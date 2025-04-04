/*
 * LL_R2000.c
 *
 *  Created on: Dec 9, 2024
 *      Author: Dany
 */

#ifndef _LL_R2000_H_
#define _LL_R2000_H_

#include "tcp.h"
#include "udp.h"
#include "lwip.h"

extern struct netif gnetif;

typedef enum LL_R2000_operation_e {
	none = 0,
	http_request = 1,
	data_stream_udp = 2, // currently, the only type of conexion supported using udp is a data stream
	data_stream_tcp = 3,
} LL_R2000_operation_t;

typedef enum http_code_e {
	no_code = 0,

	OK = 200,
	Bad_Request = 400, // wrong URI syntax or URI too long
	Forbidden = 403, // permission denied for this URI
	Not_Found = 404,  // unknown command code or unknown URI
	Method_not_allowed = 405, // invalid method requested (currently only GET is allowed)
} http_code_t ;

typedef enum R2000_error_code_e {
	success = 0,
	unknown_argument = 100,
	unknown_parameter = 110,
	invalid_handle = 120, //or no handle provided
	argument_missing = 130,
	invalid_value = 200,
	out_of_range = 210,
	read_only = 220, //write-access to read-only parameter
	insufficient_memory = 230,
	in_use = 240, // resource already/still in use
	unknown_error = 333, // (internal) error while processing command
} R2000_error_code_t;

typedef struct LL_R2000_s{
	char* label;
	ip_addr_t addr;

	LL_R2000_operation_t operation;
	http_code_t http_code; // http return code for a request (only applicable for http_request operations

	uint16_t port; // incoming connnexions are not supported, as the lidar should never initiate one by itself

	err_t (*sent_callback)(struct LL_R2000_s* ctrl); // when the operation has been done (request sent)
	err_t (*received_callback)(struct LL_R2000_s* ctrl, struct pbuf *p); // when data is received

	void* args; // WARNING : args is not copied by the lib, and the user should always make sure that it is a valid pointer (by allocating it or defining it at compile time)
} LL_R2000_t;

err_t lidarContact(LL_R2000_t* LL_control_struct);

#endif
