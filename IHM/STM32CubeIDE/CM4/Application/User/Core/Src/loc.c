#include "loc.h"

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define VERBOSE

static float _dist(float x1, float y1, float x2, float y2){return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));}
static bool _inside(float x, float y, float x1, float y1, float x2, float y2){return (x > x1 && x < x2 && y > y1 && y < y2);}

void setPosition(loc_t* handle, float x, float y, float theta){
    handle->robot.x = x;
    handle->robot.y = y;
    handle->robot.t = theta;

    handle->robot.trsl_spd = 0;
    handle->robot.angular_spd = 0;
    handle->robot.trvled_x = 0;
    handle->robot.trvled_y = 0;
    handle->robot.trvled_t = 0;
    handle->robot.trvled_dist = 0;

    handle->prev_robot = handle->robot;

    for(uint16_t i = 0; i < NUM_BEACONS; i ++){ // as we know where we are, and know the position of every beacon on the table, just associate them
        handle->tracked_beacons[i].lock = false;
        //handle->tracked_beacons[i].x = handle->field.beacons[i].x;
        //handle->tracked_beacons[i].y = handle->field.beacons[i].y;
        //handle->tracked_beacons[i].dist = _dist(x, y, handle->field.beacons[i].x, handle->field.beacons[i].y);
        //handle->tracked_beacons[i].angle = atan2(y, x) + theta;

        //while(handle->tracked_beacons[i].angle < M_PI) handle->tracked_beacons[i].angle += 2*M_PI;
        //while(handle->tracked_beacons[i].angle >= M_PI) handle->tracked_beacons[i].angle -= 2*M_PI;
    }
}

// TODO : utiliser l'accélération
// TODO : invalider une association si un autre point est trop proche (et qu'il y en a deux autres disponnibles)
void updateField(loc_t* handle, lidar_point_t points[], uint16_t points_nb, uint32_t dt_ms){

    // first, we determine the speed of the robot
    handle->robot.trvled_x = handle->robot.x - handle->prev_robot.x;
    handle->robot.trvled_y = handle->robot.y - handle->prev_robot.y;
    handle->robot.trvled_t = handle->robot.t - handle->prev_robot.t;

    handle->robot.trvled_dist = sqrt(handle->robot.trvled_x*handle->robot.trvled_x + handle->robot.trvled_y*handle->robot.trvled_y); // distance traveled
    handle->robot.trvl_t = atan2(handle->robot.trvled_y, handle->robot.trvled_x); // angle at which that distance was traveled

    handle->robot.trsl_spd = ((float)dt_ms/1000.0) * handle->robot.trvled_dist; // speed at which that distance was traveled
    handle->robot.trsl_spd_delta = (handle ->robot.trsl_spd - handle->prev_robot.trsl_spd);

    handle->robot.angular_spd = ((float)dt_ms/1000.0) * handle->robot.trvled_t;
    handle->robot.angular_spd_delta = (handle ->robot.angular_spd - handle->prev_robot.angular_spd);


    printf("toler : ");
    //then, determine the tolerance we have on beacon positions according to current speed
    for(uint16_t i = 0; i < NUM_BEACONS; i++){
        // TODO : tolerance according to speed
    	handle->tracked_beacons[i].tolerance = ((handle->tracked_beacons[i].dist + handle->robot.trvled_dist + handle->robot.trsl_spd_delta) * fabsf(handle->robot.trvled_t + handle->robot.angular_spd_delta)) + handle->robot.trvled_dist + handle->robot.trsl_spd_delta;
    	handle->tracked_beacons[i].tolerance *= handle->tolerance_coef +1;
    	handle->tracked_beacons[i].tolerance += handle->tolerance_base;


    	printf("\t%.2f ", handle->tracked_beacons[i].tolerance);
    }
    printf("\n");

    handle->prev_robot = handle->robot; // save current state for future calculations

#ifdef VERBOSE
    printf("travel x %.2f y %.2f trsl %.2f (towards %.4f), ang %.4f\n", handle->robot.trvled_x, handle->robot.trvled_y, handle->robot.trvled_dist, handle->robot.trvl_t, handle->robot.trvled_t);
    printf("spd trsl %.2f rot %.4f\n", handle->robot.trsl_spd, handle->robot.angular_spd);
#endif

    // then we can start the tracking operations
    for(uint16_t i = 0; i < NUM_BEACONS; i++) handle->tracked_beacons[i].lock = false; // start by considering every beacon is lost
    for(uint16_t i = 0; i < points_nb; i++) points[i].type = unknown; // and that every point seen by the lidar is of unknown type

    for(uint16_t i = 0; i < points_nb; i++){
        // calculate the absolute corrdinates of the beacons according to the current position, taking speed into account to determine the expected position at time of the measure

    	// todo : note : acc is not taken into account in the xy axies, but is in the t axis
    	points[i].x = points[i].distance*cos(points[i].angle + handle->robot.t + handle->robot.trvled_t + handle->robot.angular_spd_delta) + handle->robot.x + handle->robot.trvled_x;
        points[i].y = points[i].distance*sin(points[i].angle + handle->robot.t + handle->robot.trvled_t + handle->robot.angular_spd_delta) + handle->robot.y + handle->robot.trvled_y;

        for(uint16_t j = 0; j < NUM_BEACONS; j++){ // then check if a real life beacon is indeed there
#ifdef VERBOSE
            //printf("point %d : comparing... x %.2f y %.2f (lidar) to x %.2f y %.2f (expected), dist %.2f (tolerance %.2f)\n", i, points[i].x, points[i].y, handle->field.beacons[j].x, handle->field.beacons[j].y, _dist(handle->field.beacons[j].x, handle->field.beacons[j].y, points[i].x, points[i].y), handle->tracked_beacons[j].tolerance);
#endif
            if(_dist(handle->field.beacons[j].x, handle->field.beacons[j].y, points[i].x, points[i].y) <= handle->tracked_beacons[j].tolerance){ // if so, save the distance and angle to that beacon
#ifdef VERBOSE
                printf("match ! (id %d, dist %.2f, toler %.2f)\n", j, _dist(handle->field.beacons[j].x, handle->field.beacons[j].y, points[i].x, points[i].y), handle->tracked_beacons[j].tolerance);

                printf(">dist%d:%.2f\n", j,_dist(handle->field.beacons[j].x, handle->field.beacons[j].y, points[i].x, points[i].y));
#endif
                handle->tracked_beacons[j].dist = points[i].distance;
                handle->tracked_beacons[j].angle = points[i].angle;
                handle->tracked_beacons[j].lock = true;
                points[i].type = beacon;
            }
        }

        uint16_t adv_cnt = 0;
        for(uint16_t j = 0; j < points_nb; j++){
            if(points[j].type == unknown){ // point has not been attributed yet
                if(_inside(points[j].x, points[j].y, handle->field.x1, handle->field.y1, handle->field.x2, handle->field.y2)){ // point is inside the playing field
                    points[j].type = adversary;
                    handle->adversaries[adv_cnt].x = points[j].x;
                    handle->adversaries[adv_cnt].y = points[j].y;

                    adv_cnt++;
                }
            }
        }
    }
}

static void trilateration(point_t refs[], float d1, float d2, float d3, robot_t* result) {
    float A = 2 * (refs[1].x - refs[0].x);
    float B = 2 * (refs[1].y - refs[0].y);
    float C = d1 * d1 - d2 * d2 - refs[0].x * refs[0].x - refs[0].y * refs[0].y + refs[1].x * refs[1].x + refs[1].y * refs[1].y;

    float D = 2 * (refs[2].x - refs[0].x);
    float E = 2 * (refs[2].y - refs[0].y);
    float F = d1 * d1 - d3 * d3 - refs[0].x * refs[0].x - refs[0].y * refs[0].y + refs[2].x * refs[2].x + refs[2].y * refs[2].y;

    float denominator = A * E - B * D;
    if (fabs(denominator) < 1e-6) {
        printf("Unable to locate\n");
        return;
    }

    result->x = (C * E - B * F) / denominator;
    result->y = (A * F - C * D) / denominator;
}


static void bilateration(loc_t* handle, uint16_t valid_1, uint16_t valid_2) {
	float x0 = handle->field.beacons[valid_1].x, y0 = handle->field.beacons[valid_1].y;
    float x1 = handle->field.beacons[valid_2].x, y1 = handle->field.beacons[valid_2].y;

    float d1 = handle->tracked_beacons[valid_1].dist;
    float d2 = handle->tracked_beacons[valid_2].dist;

    float d = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));

    if (d > d1 + d2 || d < fabs(d1 - d2)) {
        printf("Unable to locate (2 beacons)\n");
        return;
    }

    float a = (d1 * d1 - d2 * d2 + d * d) / (2 * d);
    float h = sqrt(d1 * d1 - a * a);

    float xm = x0 + a * (x1 - x0) / d;
    float ym = y0 + a * (y1 - y0) / d;

    float xs1 = xm + h * (y1 - y0) / d;
    float ys1 = ym - h * (x1 - x0) / d;

    float xs2 = xm - h * (y1 - y0) / d;
    float ys2 = ym + h * (x1 - x0) / d;

    if (fabs(h) < 1e-6) {
    	handle->robot.x = xs1;
        handle->robot.y = ys1;
    } else {
    	if (_dist(xs1, ys1, handle->robot.x, handle->robot.y) < _dist(xs2, ys2, handle->robot.x, handle->robot.y)) {
    		handle->robot.x = xs1;
    		handle->robot.y = ys1;
        } else {
        	handle->robot.x = xs2;
        	handle->robot.y = ys2;
        }
    }
}

static void angleFinder(robot_t* robot, point_t* ref, beacon_t* meas){ // needs position to be determined !

    float ref_angle = atan2f((ref->y - robot->y), (ref->x - robot->x));

    robot->t = ref_angle - meas->angle; // the beacon's angle relative to the coordinates system, minus the beacon's angle relative to the robot

    while(robot->t < M_PI) robot->t += 2*M_PI;
    while(robot->t >= M_PI) robot->t -= 2*M_PI;
#ifdef VERBOSE
    printf("angle rob_t %.3f ref %.3f meas %.3f \n", robot->t, ref_angle, meas->angle);
#endif
}

void computePosition(loc_t* handle){
    uint16_t nb_beacons = 0;
    for(uint16_t i = 0; i < NUM_BEACONS; i ++){ // first, figure out how many of the beacons we can see (and use)
        if(handle->tracked_beacons[i].lock) nb_beacons++;
    }

    switch (nb_beacons){
        default :
            printf("More than 3 beacons available, using only 3\n");
        case 3 :
            trilateration(handle->field.beacons, handle->tracked_beacons[0].dist, handle->tracked_beacons[1].dist, handle->tracked_beacons[2].dist, &(handle->robot));
            angleFinder(&(handle->robot),&(handle->field.beacons[0]), &(handle->tracked_beacons[0]));
            break;
        case 2 :
        	uint16_t valid_1 = -1;
			uint16_t valid_2 = -1;

        	for(uint16_t i = 0; i < NUM_BEACONS; i++){
        		if(handle->tracked_beacons[i].lock){
        			if(valid_1 == (uint16_t)-1) valid_1 = i;
        			else valid_2 = i;
        		}
        	}

            bilateration(handle, valid_1, valid_2);
            angleFinder(&(handle->robot),&(handle->field.beacons[valid_1]), &(handle->tracked_beacons[valid_1]));
        case 1 : // figure out position based on only one beacon is both impossible without another source of information, and risky, as we could quite easily loose it
        case 0 :
            printf("Not enough beacons !\n");
            break;
    }
}
