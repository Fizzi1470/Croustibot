/*
 * R2000.c
 *
 *  Created on: Nov 25, 2024
 *      Author: Dany
 */

#include "tcp.h"
#include "udp.h"
#include "lwip.h"

#include "R2000.h"
#include "R2000_commands.h"

#include <stdio.h>
#include <string.h>

// ==================== Variables ==================== //

void lidarInit(R2000_t* lidar, uint8_t addr_A, uint8_t addr_B, uint8_t addr_C, uint8_t addr_D){
	IP4_ADDR(&(lidar->address), addr_A, addr_B, addr_C, addr_D);

	printf("R2000 : Init\n");
}


void lidarProcess(){
	  ethernetif_input(&gnetif);
	  sys_check_timeouts();
}

void lidarRequest(R2000_t* lidar, lidar_commands_t command, lidar_parameters_t param, int32_t value){
	httpCommand(lidar->address,command,param,value);
}

void lidarPrintLocalIP(R2000_t* lidar){

	uint32_t IP = gnetif.ip_addr.addr;
	uint32_t netmask = gnetif.netmask.addr;
	uint32_t gateway = gnetif.gw.addr;

	char IP_str[17];
	char gateway_str[17];
	char netmask_str[17];

	sprintf(IP_str, "%ld.%ld.%ld.%ld",(IP & 0xff), ((IP >> 8) & 0xff), ((IP >> 16) & 0xff), (IP >> 24));
	sprintf(gateway_str, "%ld.%ld.%ld.%ld",(gateway & 0xff), ((gateway >> 8) & 0xff), ((gateway >> 16) & 0xff), (gateway >> 24));
	sprintf(netmask_str, "%ld.%ld.%ld.%ld",(netmask & 0xff), ((netmask >> 8) & 0xff), ((netmask >> 16) & 0xff), (netmask >> 24));

	printf("R2000 : Local\n\tIP : %s\n\tGW : %s\n\tMask : %s\n", IP_str, gateway_str, netmask_str);
}


