#include "LL_R2000.h"

#include <string.h>
#include <stdio.h>

#include "LL_R2000.h"
#include "R2000_commands.h"
#include "parser.h"

#define VERBOSE_MODE

static const char* commands[] = {
	"list_parameters",
	"get_parameter",
	"set_parameter",
	"reset_parameter",
	"reboot_device",
	"factory_reset",
};

static const char* parameters[] = {
	"vendor",
	"product",
	"part",
	"serial",
	"revision_fw",
	"revision_hw",
	"max_connections",
	"feature_flags",
	"radial_range_max",
	"radial_range_min",
	"radial_resolution",
	"angular_fov",
	"angular_resolution",
	"ip_mode",
	"ip_address",
	"subnet_mask",
	"gateway",
	"scan_frequency",
	"scan_direction",
	"samples_per_scan",
	"scan_frequency_measured",
	"status_flags",
	"load_indication",
	"up_time",
	"power_cycles",
	"operation_time",
	"operation_time_scaled",
	"temperature_current",
	"temperature_min",
	"temperature_max",
	"contamination",
	"user_tag",
	"device_family",
	"mac_address",
	"hmi_display_mode",
	"hmi_language",
	"hmi_button_lock",
	"hmi_parameter_lock",
	"ip_mode_current",
	"ip_address_current",
	"subnet_mask_current",
	"gateway_current",
	"system_time_raw",
	"user_notes",
	"locator_indication",
	"scan_frequency_min",
	"scan_frequency_max",
	"sampling_rate_min",
	"sampling_rate_max",
	"hmi_static_text_1",
	"hmi_static_text_2",
	"hmi_application_text_1",
	"hmi_application_text_2",
	"hmi_static_logo",
	"hmi_application_bitmap",
	"operating_mode",
	"emitter_type",
	"filter_type",
	"filter_width",
	"filter_error_handling",
	"filter_remission_threshold",
	"filter_maximum_margin",
	"lcm_num_sectors",
	"lcm_detection_sensitivity",
	"lcm_detection_period",
	"lcm_sector_enable",
	"lcm_sector_warn_flags",
	"lcm_sector_error_flags"
};

static err_t _responseReceivedCallback(LL_R2000_t* ctrl, struct pbuf *p){

	if(p -> len != 0){
		/*
		#ifdef VERBOSE_MODE
		printf("%s", (uint8_t*)p->payload);
		#endif
		*/

		tokens_t tokens = {0};

		parse(&tokens, (uint8_t*)p->payload, p->len);
		#ifdef VERBOSE_MODE
		printf("R2000_CMD : %s : Parsed :\n", ctrl->label);
		for(int i = 0; i < tokens.nb; i++){
			//printf("mark : %d %d %d %d\n", tokens.tokens[i].head_start, tokens.tokens[i].head_end, tokens.tokens[i].data_start, tokens.tokens[i].data_end);
			printf("\tToken %d : %s : %s\n", i, getHeader(p->payload,&tokens.tokens[i]), getData(p->payload,&tokens.tokens[i]));
		}
		#endif

	}

	return ERR_OK;
}


static err_t _requestSentCallback(LL_R2000_t* ctrl){
	((char*)ctrl->args)[strlen(((char*)ctrl->args)) - 4] = '\0'; // cut the line and carriage return before printing to terminal
	#ifdef VERBOSE_MODE
	printf("R2000_CMD : %s : HTTP request sent %s\n", ctrl->label, (char*)(ctrl->args));
	#endif

	return ERR_OK;
}

err_t httpCommandRaw(ip_addr_t address, char* command, char* label, err_t (*received_callback)(struct LL_R2000_s* ctrl, struct pbuf *p)){

	char* request = mem_malloc(strlen(command) +1);
	char* label_ptr = mem_malloc(strlen(label) +1);

	if(request == NULL || label_ptr == NULL){

		if(request != NULL) mem_free(request);
		if(label_ptr != NULL) mem_free(label_ptr);

		#ifdef VERBOSE_MODE
		printf("R2000_CMD : error ! not enough memory for %s\n", label);
		#endif
		return ERR_MEM; // could not create the request, abort
	}

	memcpy(label_ptr, label , strlen(label) +1); // +1 to include the end of string marker ('\0')
	memcpy(request, command, strlen(command) +1); // +1 to include the end of string marker ('\0')

	LL_R2000_t ctrl = {
		.label = label_ptr,
		.addr = address,
		.args = request,
		.operation = http_request,
		.port = 80,
		.sent_callback = _requestSentCallback,
		.received_callback = received_callback,
	};

	lidarContact(&ctrl);

	return ERR_OK;
}

err_t httpCommandText(ip_addr_t address, char* command, char* label){
	httpCommandRaw(address, command, label, _responseReceivedCallback);
}

err_t httpCommand(ip_addr_t address, lidar_commands_t command, lidar_parameters_t param, int32_t value){
	char string[256];

	switch (command){
	case get :
		sprintf(string, "GET /cmd/%s?list=%s HTTP/1.1\r\n\r\n", commands[command], parameters[param]);
		break;
	default :
		sprintf(string, "GET /cmd/%s?%s=%ld HTTP/1.1\r\n\r\n", commands[command], parameters[param], value);
		break;
	}

	httpCommandText(address, string, "User command");
}
