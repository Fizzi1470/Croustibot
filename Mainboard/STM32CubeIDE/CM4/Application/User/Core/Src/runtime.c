#include "runtime.h"
#include "R2000.h"
#include "loc.h"

#include <math.h>

R2000_t lidar;
/*
loc_t loc = {
	.field = {
		 .beacons = {
			{.x = -400, .y = 0},
			{.x = 0, .y = 1440},
			{.x = 1575, .y = 0},
		},
		.x1 = -1000,
		.y1 = -1000,
		.x2 = 1000,
		.y2 = 1000,
	},

	.min_tolerance = 300,
	.tolerance_coef = 0,
};
*/
loc_t loc = {
	.field = {
		 .beacons = {
			{.x = 1400 - 40, .y = 1997 - 40},
			{.x = 40, .y = 1997 - 40},
			{.x = 40, .y = 40},
		},
		.x1 = 0,
		.y1 = 1997,
		.x2 = 1400,
		.y2 = 0,
	},

	.tolerance_base = 100,
	.tolerance_coef = 0.5,
};

robot_t true_robot = { .x = 1400 - 300, .y = 300, .t = - M_PI/2};

#define MIN_AMP_FILTER 1000
#define MAX_GAP_FILTER 10
#define BEACON_RADIUS 40
lidar_point_t remarkable_pts[MAX_POINTS_PER_SCAN] = {0};

uint32_t last_tick = 0;

float _random(float min, float max){
    int random = rand()%(int)(max*100.0 - min*100.0 +1);
    return ((float) random / 100.0) + min;
}
static float _dist(float x1, float y1, float x2, float y2){return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));}

void testingMove(loc_t* handle, robot_t* true_robot, lidar_point_t points[], float range_xy, float range_t){

    float random = _random(0,range_xy);
    printf("Robot move : x %.2f, ", random);
    true_robot->x += random;
    random = _random(0,range_xy);
    printf("y %.2f, ", random);
    true_robot->y += random;
    random = _random(0,range_t);
    printf("t %.4f\n", random);
    true_robot->t += random;

    //true_robot->x += range_xy;
    //true_robot->y += range_xy;
    //true_robot->t += range_t;

    while(true_robot->t < M_PI) true_robot->t += 2*M_PI;
    while(true_robot->t >= M_PI) true_robot->t -= 2*M_PI;

    lidar_point_t buffer[NUM_BEACONS] = {0};

    printf("simulated beacons :\n");
    for (uint16_t i = 0; i < NUM_BEACONS; i++){
        float x = handle->field.beacons[i].x - true_robot->x;
        float y = handle->field.beacons[i].y - true_robot->y;

        buffer[i].distance = _dist(true_robot->x, true_robot->y, handle->field.beacons[i].x, handle->field.beacons[i].y);
        buffer[i].angle = atan2(y, x) - true_robot->t;

        while(buffer[i].angle < M_PI) buffer[i].angle += 2*M_PI;
        while(buffer[i].angle >= M_PI) buffer[i].angle -= 2*M_PI;

        printf("dist %.2f ang %.2f x %.2f y %.2f\n", buffer[i].distance, buffer[i].angle, x, y);
    }
    printf("\n");

    for(uint16_t i = 0; i < NUM_BEACONS; i++){
        points[i] = buffer[NUM_BEACONS - i -1];
        //points[i] = buffer[i];
    }

    printf("simulated robot :\nx %.2f y %.2f t %.4f\n", true_robot->x, true_robot->y, true_robot->t);
}

static uint16_t _isolateBeacons(R2000_data_point_t* buff, uint16_t buff_amnt, uint16_t buff_max, lidar_point_t* lidar_filtered){
	uint16_t last_valid = 0;
	uint16_t valid_amnt = 0;


	uint32_t dist_sum = 0;
	uint32_t ang_sum = 0;

	uint16_t out_index = 0;

	int32_t offset = 0;
	for(int32_t i = 0; i < offset + MAX_GAP_FILTER; i++){ // offset the whole thing by the amount of valid continuous points in the negative values to handle crossing 0
		if(buff[buff_max - i].amplitude > MIN_AMP_FILTER) offset = i;
	}
	//printf("offset %ld\n", offset);

	for(int32_t i = offset; i < buff_amnt + offset + MAX_GAP_FILTER; i++){

		if(buff[i % buff_max].amplitude > MIN_AMP_FILTER){
			last_valid = i;
			dist_sum += buff[i % buff_max].distance;
			ang_sum += i;
			valid_amnt++;

			//printf("point %ld valid\n", i);
		}

		if((i - last_valid > MAX_GAP_FILTER) && valid_amnt != 0){ // last valid point was too far, compute and consider as a beacon
			lidar_filtered[out_index].distance = ((float)dist_sum / ((float) valid_amnt)) + BEACON_RADIUS;
			float raw_angle = ((float)ang_sum) / ((float) valid_amnt); // moyenne
			//float raw_angle = last_valid - ((float) valid_amnt / 2.0); // medianne
			lidar_filtered[out_index].angle = (raw_angle * (2*M_PI)) / (float)buff_max;

			while(lidar_filtered[out_index].angle > M_PI) lidar_filtered[out_index].angle -= 2*M_PI;
			while(lidar_filtered[out_index].angle <= -M_PI) lidar_filtered[out_index].angle += 2*M_PI;

			//printf("raw %.2f\n",raw_angle);

			out_index ++;
			dist_sum = 0;
			ang_sum = 0;
			valid_amnt = 0;
		}
	}

	return out_index;
}


inline void setup(){
	lidarInit(&lidar,192,168,1,4);
	lidarPrintLocalIP(&lidar);

	startDataStreamUDP(lidar.address);

    setPosition(&loc, true_robot.x, true_robot.y, true_robot.t);
}

inline void loop(){
	lidarProcess();

	if(full_scan_ready){
		uint32_t tick = HAL_GetTick();

		printf("\n\nfull scan %d/%d pts, %.1f Hz\n", points_received, points_to_be_received, 1000.0/((float)(tick - last_tick)));

		uint16_t pts_found = _isolateBeacons(lidar_points, points_received, points_to_be_received, remarkable_pts);

		printf(">valid_pts:");
		printf("%.f:%.f;%.f:%.f;", loc.field.x1, loc.field.y1, loc.field.x2, loc.field.y2);
		for(uint16_t i = 0; i < points_received; i++){
			if(lidar_points[i].amplitude > 150)
				printf("%.2f:%.2f;", lidar_points[i].distance * cos((((float)i * M_PI) / points_to_be_received) - loc.robot.t) + loc.robot.x, lidar_points[i].distance * sin((((float)i * M_PI) / points_to_be_received) - loc.robot.t) + loc.robot.y);
		}
		printf("|xy,clr\n");


		for(uint16_t i = 0; i < pts_found; i++){
			printf("beacon dist %.2f ang %.2f (x %.3f y %.3f rel ; x %.3f y %.3f abs)\n", remarkable_pts[i].distance, remarkable_pts[i].angle, remarkable_pts[i].distance * cos(remarkable_pts[i].angle), remarkable_pts[i].distance * sin(remarkable_pts[i].angle), remarkable_pts[i].distance * cos(remarkable_pts[i].angle) + loc.robot.x, remarkable_pts[i].distance * sin(remarkable_pts[i].angle) + loc.robot.y);
		}

		printf(">beac_nb:%df\n", pts_found);

		//testingMove(&loc, &true_robot, lidar_pts, 20, 0.1);

		updateField(&loc, remarkable_pts, pts_found, tick - last_tick);
		computePosition(&loc);

		printf("robot x %.2f y %.2f t %.4f trsl_spd %.2f rot_spd %.2f trvled %.2f\n",
				 loc.robot.x,
		         loc.robot.y,
		         loc.robot.t,
		         loc.robot.trsl_spd,
		         loc.robot.angular_spd,
				 loc.robot.trvled_t
		 );

		printf(">pos:");
		printf("%.f:%.f;%.f:%.f;", loc.field.x1, loc.field.y1, loc.field.x2, loc.field.y2);
		for(uint16_t i = 0; i < pts_found; i++){
			printf("%.2f:%.2f;", remarkable_pts[i].x, remarkable_pts[i].y);
		}
		printf("%.2f:%.2f;", loc.robot.x, loc.robot.y);
		printf("|xy,clr\n");

		printf(">ang:%.2f\n", loc.robot.t);
		printf(">trsl_spd:%.3f\n", loc.robot.trsl_spd);
		printf(">rot_spd:%.5f\n", loc.robot.angular_spd);

		for(uint16_t i = 0; i < 3; i++){
			if(loc.tracked_beacons[i].lock) printf(">toler%d:%.2f\n",i, loc.tracked_beacons[i].tolerance);
		}

		full_scan_ready = false;
		points_received = 0;
		last_tick = tick;
	}
}
