/*
 * R2000.h
 *
 *  Created on: Nov 18, 2024
 *      Author: Dany
 */

#ifndef INC_R2000_H_
#define INC_R2000_H_

#include "R2000_commands.h"
#include "R2000_data.h"

#include <stdbool.h>

typedef struct {
	ip_addr_t address;
} R2000_t;

extern uint16_t points_to_be_received;
extern uint16_t points_received;
extern R2000_data_point_t lidar_points[MAX_POINTS_PER_SCAN];
extern bool full_scan_ready;

void lidarInit(R2000_t* lidar, uint8_t addr_A, uint8_t addr_B, uint8_t addr_C, uint8_t addr_D);

void lidarProcess();

void lidarRequest(R2000_t* lidar, lidar_commands_t command, lidar_parameters_t param, int32_t value);

void lidarPrintLocalIP(R2000_t* lidar);


#endif /* INC_R2000_H_ */
