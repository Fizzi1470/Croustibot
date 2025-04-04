/*
 * R2000_data.c
 *
 *  Created on: Dec 9, 2024
 *      Author: Dany
 */

#include "LL_R2000.h"
#include "R2000_data.h"
#include "R2000_commands.h"
#include "parser.h"

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define VERBOSE_MODE
#define TELEPLOT

static const uint16_t incoming_udp_data_port = 12345;

uint16_t points_to_be_received = 0;
uint16_t points_received = 0;
bool full_scan_ready = false;
R2000_data_point_t lidar_points[MAX_POINTS_PER_SCAN];
const uint16_t magic = 0xa25c;

static err_t _dataReceivedCallback(LL_R2000_t* ctrl, struct pbuf *p){
/* trying to find the magic bytes each time has proved too time consuming, and the data seems to always start at 0
	uint16_t offset = pbuf_memfind(p, &magic, 2, 0);

	if(offset == 0xFFFF){
		printf("no usable data\n");
		return;
	}
	if(offset){
		printf("data cut\n");
	}
*/

	R2000_data_header_t* header = (R2000_data_header_t*) &((uint8_t*)(p->payload))[/*offset +*/2]; // skip the magic bytes (2)
/*
	printf("len %d %d\n",p->len,p->tot_len);

	printf("pack type %c\n", header->packet_type);
	printf("pack size %d\n", header->packet_size);
	printf("head size %d\n", header->header_size);
	printf("scan num %d\n", header->scan_number);
	printf("pack num %d\n", header->packet_number);
	printf("time %ld\n", header->timestamp_raw);
	printf("status %ld\n", header->status_flags);
	printf("scan_freq %ld\n", header->scan_frequency);
	printf("num pts scan %d\n", header->num_points_scan);
	printf("num pts pack %d\n", header->num_points_packet);
	printf("frst index %d\n", header->first_index);
	printf("frst angle %d\n", header->first_angle);
	printf("angular incre %ld\n", header->angular_increment);
	printf("iq input %X\n", header->iq_input);
	printf("iq ovld %X\n", header->iq_overload);
	printf("iq time %ld\n", header->iq_timestamp_raw);
*/
	R2000_data_point_t* point = (R2000_data_point_t*) &((uint8_t*)(p->payload))[/*offset +*/header->header_size];
	uint16_t cursor = header -> first_index;

	for (uint16_t i = 0; i < header->num_points_packet; i++, cursor++){
		if(cursor >= MAX_POINTS_PER_SCAN){
			printf("Warning ! point buffer end reached ! (are you getting more than %d points per scan ?)", MAX_POINTS_PER_SCAN);
			cursor = 0;
		}

		lidar_points[cursor] = point[i];

		//if(point[i].amplitude > 500 && point[i].amplitude < 4096)
		//	printf("p%d dis%ld am%d\n",cursor, point[i].distance, point[i].amplitude);
	}

	points_received += header->num_points_packet;

	if(cursor == header->num_points_scan){
		points_to_be_received = header->num_points_scan;
		full_scan_ready = true; // consider that, if the cursor reaches the end of the scan points, a full scan has been received
	}
}

static err_t _responseReceivedCallback(LL_R2000_t* ctrl, struct pbuf *p){
	if(p -> len == 0) return ERR_VAL;

	/*
	#ifdef VERBOSE_MODE
	printf("R2000_DAT : %s : Raw response : \n%s", ctrl->label, (uint8_t*)p->payload);
	#endif
	*/

	tokens_t tokens = {0};
	parse(&tokens, (uint8_t*)p->payload, p->len);

	#ifdef VERBOSE_MODE
	printf("R2000_DAT : %s : Parsed :\n", ctrl->label);
	for(int i = 0; i < tokens.nb; i++){
		//printf("mark : %d %d %d %d\n", tokens.tokens[i].head_start, tokens.tokens[i].head_end, tokens.tokens[i].data_start, tokens.tokens[i].data_end);
		printf("\tToken %d : %s : %s\n", i, getHeader(p->payload,&tokens.tokens[i]), getData(p->payload,&tokens.tokens[i]));
	}
	#endif

//#error huuummm ... il ne semble pas trouver de port dans les tokens ?

	R2000_data_stream_t* metadata = mem_malloc(sizeof(R2000_data_stream_t));

	char label[] = {"Data stream"};

	char* label_ptr = mem_malloc(strlen(label));

	if(metadata == NULL || label_ptr == NULL){

		if(metadata != NULL) mem_free(metadata);
		if(label_ptr != NULL) mem_free(label_ptr);

		#ifdef VERBOSE_MODE
		printf("R2000_DAT : %s : Not enough memory !\n", ctrl->label);
		#endif
		return ERR_MEM; // could not create the request, abort
	}

	memcpy(label_ptr, label, strlen(label) + 1);

	for (uint16_t i = 0; i < tokens.nb; i++){
		if(is_header("port")){
			get_data_short(metadata->port);
		} else if (is_header("handle")) {
			get_data_str(metadata->handle);
		} else if (is_header("error_code")) {
			get_data_long(metadata->error_code);
		}
	}

	metadata->type = udp; // WARNING : StartDataStream's type needs to match this !!!
	// TODO : make the user select the connexion type
	// TODO : implement udp (need to bind to the port returned by the sensor)

	if(metadata->type == udp){
		metadata->port = incoming_udp_data_port;
	} else {
		if(metadata->port == 0){
			#ifdef VERBOSE_MODE
			printf("R2000_DAT : %s : Returned port is 0, aborting ...\n", ctrl->label);
			#endif
			mem_free(metadata);
			mem_free(label_ptr);
			return ERR_VAL;
		}
	}

	LL_R2000_t stream_ctrl = {
		.label = label_ptr,
		.addr = ctrl->addr,
		.args = metadata,
		.operation = (metadata->type == tcp ? data_stream_tcp : data_stream_udp),
		.port = metadata->port,
		.received_callback = _dataReceivedCallback,
	};

	lidarContact(&stream_ctrl);

	char string[256];
	sprintf(string, "GET /cmd/start_scanoutput?handle=%s HTTP/1.1\r\n\r\n", metadata->handle);
	httpCommandText(ctrl->addr, string, "Scan start");

	return ERR_OK;
}

err_t startDataStreamUDP(ip_addr_t address){
	char string[256];

	char local_ip[17];
	uint32_t IP = gnetif.ip_addr.addr;
	sprintf(local_ip, "%ld.%ld.%ld.%ld",(IP & 0xff), ((IP >> 8) & 0xff), ((IP >> 16) & 0xff), (IP >> 24));

	sprintf(string, "GET /cmd/request_handle_udp?"
					"&packet_type=B"
					"&watchdog=off"

					"&address=%s"
					"&port=%d"
					//"&skip_scans=19"

					" HTTP/1.1\r\n\r\n", local_ip, incoming_udp_data_port);

	httpCommandRaw(address, string, "Handle rqst UDP", _responseReceivedCallback);

	char filter_width[] = {"GET /cmd/set_parameter?filter_width=2 HTTP/1.1\r\n\r\n"};
	char filter_type[] = {"GET /cmd/set_parameter?filter_type=remission HTTP/1.1\r\n\r\n"};
	char filter_reflector[] = {"GET /cmd/set_parameter?filter_remission_threshold=reflector_std HTTP/1.1\r\n\r\n"};
	char filter_treshold[] = {"GET /cmd/set_parameter?filter_remission_threshold=reflector_std HTTP/1.1\r\n\r\n"};

	//httpCommandText(address, filter_type, "Filter Type");
	//httpCommandText(address, filter_width, "Filter Width");
	//httpCommandText(address, filter_reflector, "Filter Reflector");
	//httpCommandText(address, filter_treshold, "Filter Treshold");

	return ERR_OK;
}

static // not implemented yet
err_t startDataStreamTCP(ip_addr_t address, int32_t start_angle){
	char string[256];

	sprintf(string, "GET /cmd/request_handle_tcp?"
					"&packet_type=B"
					"&watchdog=off"
					"&start_angle=%ld"

					" HTTP/1.1\r\n\r\n", start_angle);

	httpCommandRaw(address, string, "Handle rqst TCP", _responseReceivedCallback);

	return ERR_OK;
}
