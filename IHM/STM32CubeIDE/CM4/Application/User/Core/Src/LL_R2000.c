#include "tcp.h"
#include "udp.h"
#include "lwip.h"

#include "LL_R2000.h"

#include <string.h>

//#define VERBOSE_MODE
//#define UDP_VERBOSE

static void _terminate(LL_R2000_t* ctrl, void* pcb){
	#ifdef VERBOSE_MODE
	printf("R2000_LL : %s : Connexion terminated, memory freed\n", ctrl->label);
	#endif

	LL_R2000_operation_t op = ctrl->operation;

	mem_free(ctrl->label);
	mem_free(ctrl->args);
	mem_free(ctrl);
	if(op == data_stream_udp){
		udp_disconnect((struct udp_pcb*)pcb);
		udp_remove((struct udp_pcb*)pcb);
	} else {
		tcp_close((struct tcp_pcb*)pcb);
	}
}

static void _udpReceivedCallback(void *ctrl_void, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port){
	#ifdef VERBOSE_MODE
	#ifdef UDP_VERBOSE
	printf("R2000_LL : %s : UDP Response received of length %d (total %d)\n", ((LL_R2000_t*)ctrl_void)->label, p->len, p->tot_len);
	#endif
	#endif

	if(((LL_R2000_t*)ctrl_void)->received_callback != NULL) (*(((LL_R2000_t*)ctrl_void)->received_callback))((LL_R2000_t*)ctrl_void,p);

	pbuf_free(p);
}

static err_t _tcpReceivedCallback(void *ctrl_void, struct tcp_pcb *pcb, struct pbuf *p, err_t err){
	LL_R2000_t* ctrl = (LL_R2000_t*) ctrl_void; // WOULD SOMEONE TELL THE COMPILER TO SHUT THE FCK UP !?!

	#ifdef VERBOSE_MODE
	printf("R2000_LL : %s : TCP Response received of length %d (total %d)\n", ctrl->label, p->len, p->tot_len);
	#endif

	if(p->len > 2000) return; // TODO why the fuck is this required ?

	tcp_recved(pcb,p->len); // acknowledge the data (cannot do it at the end as we might close the pcb before doing so)

	if(ctrl->operation == http_request){
		if(p->len != 0) // strstr triggers a hardfault if provided an empty string
			if(strstr(p->payload, "HTTP") != NULL){// first, search for the keyword "HTTP", which indicates that the data is a http header and not actual data

				sscanf(p->payload + 9, "%d", (int*)&(ctrl->http_code)); // extract the number (or do nothing if there is none, which is the case for data)

				#ifdef VERBOSE_MODE
				printf("R2000_LL : %s : Response is HTTP header, Code %d\n", ctrl->label, ctrl->http_code);
				#endif
			} else if (strstr(p->payload, "{") != NULL){ // data received is usable and should be treated as a json parsable string
				#ifdef VERBOSE_MODE
				printf("R2000_LL : %s : Response is JSON data\n", ctrl->label);
				#endif

				if(ctrl->received_callback != NULL) (*(ctrl->received_callback))(ctrl,p);

				// we received our response, we can terminate the connexion now
				_terminate(ctrl, pcb);

				#ifdef VERBOSE_MODE
				printf("R2000_LL : %s : Data reception complete (transaction closed)\n", ctrl->label);
				#endif
			} else {
				printf("R2000_LL : %s : Response of unknown form, cannot read\n", ctrl->label);
			}
	} else if (ctrl->operation == data_stream_tcp){
		#ifdef VERBOSE_MODE
		printf("R2000_LL : %s : Response is data stream\n", ((LL_R2000_t*)ctrl_void)->label);
		#endif
		if(ctrl->received_callback != NULL) (*(ctrl->received_callback))(ctrl,p);

		pbuf_free(p);
	}

	return ERR_OK;
}


// connection established callback, err is unused and only return 0
static err_t _tcpConnectedCallback(void *ctrl_void, struct tcp_pcb *pcb, err_t err){
	LL_R2000_t* ctrl = (LL_R2000_t*) ctrl_void; // sick and tired of casting void pointers

	#ifdef VERBOSE_MODE
	printf("R2000_LL : %s : Connected !\n", ctrl->label);
	#endif

	switch (ctrl->operation){
	case http_request:
		err_t error = tcp_write(pcb, (char*)(ctrl->args), strlen((char*)ctrl->args), TCP_WRITE_FLAG_COPY);
		#ifdef VERBOSE_MODE
		if(error) printf("R2000_LL : %s : Failed to write (error %d)\n", ctrl->label, error);
		#endif

		error = tcp_output(pcb);
		#ifdef VERBOSE_MODE
		if(error) printf("R2000_LL : %s : Failed to output (error %d)\n", ctrl->label, error);
		#endif

		if(error) return error; // tcp_output will always fail if tcp_write does
		break;
	case data_stream_tcp :

		break;
	default :
		#ifdef VERBOSE_MODE
		printf("R2000_LL : %s : Operation not supported, aborting...\n", ctrl->label);
		#endif
		_terminate(ctrl, pcb);
		return ERR_ARG;
	}

	if(ctrl->sent_callback != NULL) (*(ctrl->sent_callback))(ctrl);

	//tcp_err(pcb, tcpErrorCallback);
	tcp_recv(pcb, _tcpReceivedCallback);

	// tcp_close(pcb); // closing now makes the response retrieval abort
	return ERR_OK;
}

err_t lidarContact(LL_R2000_t* LL_control_struct){

	struct udp_pcb* udp_pcb = NULL;
	struct tcp_pcb* tcp_pcb = NULL;

	if(LL_control_struct->operation == data_stream_udp) udp_pcb = udp_new();
	else tcp_pcb = tcp_new();

	LL_R2000_t* ctrl = mem_malloc(sizeof(LL_R2000_t));

	if(ctrl == NULL || (tcp_pcb == NULL && udp_pcb == NULL)){

		if(ctrl != NULL) mem_free(ctrl);
		if(tcp_pcb != NULL) tcp_close(tcp_pcb);
		if(udp_pcb != NULL) udp_remove(udp_pcb);

		#ifdef VERBOSE_MODE
		printf("R2000_LL : %s : Not enough memory !\n", ctrl->label);
		#endif
		return ERR_MEM; // could not create the request, abort
	}

	*ctrl = *LL_control_struct; // copy the data over to save it

	if(LL_control_struct->operation == data_stream_udp) {
		udp_recv(udp_pcb, _udpReceivedCallback, ctrl);
		udp_bind(udp_pcb, &gnetif.ip_addr, ctrl->port);
	} else {
		tcp_arg(tcp_pcb, ctrl); // then save the pointer to the saved data as argument for the communication
		tcp_connect(tcp_pcb, &(ctrl->addr), ctrl->port, _tcpConnectedCallback);
	}
	#ifdef VERBOSE_MODE
	printf("R2000_LL : %s : Connecting (%s)...\n", ctrl->label, (LL_control_struct->operation == data_stream_udp ? "UDP" : "TCP"));
	#endif

	return ERR_OK;
}
