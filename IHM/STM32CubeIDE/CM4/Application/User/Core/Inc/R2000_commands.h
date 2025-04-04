/*
 * R2000_commands.h
 *
 *  Created on: Nov 25, 2024
 *      Author: Dany
 */

#ifndef INC_R2000_COMMANDS_H_
#define INC_R2000_COMMANDS_H_

#include "LL_R2000.h"

typedef enum lidar_commands_e{
	list = 0,
	get = 1,
	set = 2,
	reset = 3,
	reboot = 4,
	factory_reset = 5,
} lidar_commands_t;

typedef enum lidar_parameters_e{
	vendor = 0,
	product = 1,
	part = 2,
	serial = 3,
	revision_fw = 4,
	revision_hw = 5,
	max_connections = 6,
	feature_flags = 7,
	radial_range_max = 8,
	radial_range_min = 9,
	radial_resolution = 10,
	angular_fov = 11,
	angular_resolution = 12,
	ip_mode = 13,
	ip_address = 14,
	subnet_mask = 15,
	gateway = 16,
	scan_frequency = 17,
	scan_direction = 18,
	samples_per_scan = 19,
	scan_frequency_measured = 20,
	status_flags = 21,
	load_indication = 22,
	up_time = 23,
	power_cycles = 24,
	operation_time = 25,
	operation_time_scaled = 26,
	temperature_current = 27,
	temperature_min = 28,
	temperature_max = 29,
	contamination = 30,
	user_tag = 31,
	device_family = 32,
	mac_address = 33,
	hmi_display_mode = 34,
	hmi_language = 35,
	hmi_button_lock = 36,
	hmi_parameter_lock = 37,
	ip_mode_current = 38,
	ip_address_current = 39,
	subnet_mask_current = 40,
	gateway_current = 41,
	system_time_raw = 42,
	user_notes = 43,
	locator_indication = 44,
	scan_frequency_min = 45,
	scan_frequency_max = 46,
	sampling_rate_min = 47,
	sampling_rate_max = 48,
	hmi_static_text_1 = 49,
	hmi_static_text_2 = 50,
	hmi_application_text_1 = 51,
	hmi_application_text_2 = 52,
	hmi_static_logo = 53,
	hmi_application_bitmap = 54,
	operating_mode = 55,
	emitter_type = 56,
	filter_type = 57,
	filter_width = 58,
	filter_error_handling = 59,
	filter_remission_threshold = 60,
	filter_maximum_margin = 61,
	lcm_num_sectors = 62,
	lcm_detection_sensitivity = 63,
	lcm_detection_period = 64,
	lcm_sector_enable = 65,
	lcm_sector_warn_flags = 66,
	lcm_sector_error_flags = 67,
} lidar_parameters_t;

err_t httpCommandRaw(ip_addr_t address, char* command, char* label, err_t (*received_callback)(struct LL_R2000_s* ctrl, struct pbuf *p));
err_t httpCommandText(ip_addr_t address, char* command, char* label);
err_t httpCommand(ip_addr_t address, lidar_commands_t command, lidar_parameters_t param, int32_t value);

#endif /* INC_R2000_COMMANDS_H_ */
