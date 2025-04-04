/*
 * R2000_data.h
 *
 *  Created on: Dec 9, 2024
 *      Author: Dany
 */

#ifndef INC_R2000_DATA_H_
#define INC_R2000_DATA_H_

#include "LL_R2000.h"

#define MAX_POINTS_PER_SCAN 2400

// Refer to 3.4.5 Scan data packet type B – distance and amplitude
typedef struct __attribute__((packed)) R2000_data_header_s {
	uint16_t packet_type;
	uint32_t packet_size;
	uint16_t header_size;

	uint16_t scan_number;
	uint16_t packet_number;
	uint64_t timestamp_raw;

	uint64_t reserved;

	uint32_t status_flags;
	uint32_t scan_frequency;

	uint16_t num_points_scan;
	uint16_t num_points_packet;

	uint16_t first_index;
	int32_t first_angle;
	int32_t angular_increment;

	uint32_t iq_input;
	uint32_t iq_overload;
	uint64_t iq_timestamp_raw;

	uint64_t reserved_2;
} R2000_data_header_t;

typedef struct __attribute__((packed)) R2000_data_point_s {
	uint32_t distance;
	uint16_t amplitude;
} R2000_data_point_t;

typedef enum R2000_amplitude_e {
	no_echo = 0, // no echo receiver detected no echo
	blinding = 1, // receiver overloaded due to excessive echo amplitude
	measu_error = 2, // unable to measure echo amplitude
	// 3 - 5 reserved
	weak = 6, // detected echo too weak for a valid measurement
	// 7 - 31 reserved

	// 32 - 4095 actual data
} R2000_amplitude_t;

typedef enum stream_type_e {
	tcp = 0,
	udp = 1,
} stream_type_t;

typedef struct R2000_data_stream_s {
	stream_type_t type;
	char handle[16]; // R2000 Ethernet protocol, 3.2.2
	uint16_t port;
	R2000_error_code_t error_code;
} R2000_data_stream_t;

err_t startDataStreamUDP(ip_addr_t address);
//err_t startDataStreamTCP(ip_addr_t address, int32_t start_angle);

#endif /* INC_R2000_DATA_H_ */
