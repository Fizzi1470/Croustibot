#ifndef INC_LOC_H_
#define INC_LOC_H_

#define NUM_BEACONS 3
#define NUM_ADVERSARIES 3

#include <stdbool.h>
#include <stdint.h>

// TODO : add fixed tolerance to a lost beacon, to be able to re-lock it (without the tolerance radius becoming too big)

typedef enum {
    unknown = 0,
    adversary = 1,
    beacon = 2,
} lidar_point_type_t;

typedef struct {
    float x;
    float y;
    float t;

    float trsl_spd; // xy speed
    float angular_spd; // angular speed

    float trsl_spd_delta;
    float angular_spd_delta;

    float trvled_x; // distance traveled since last computation
    float trvled_y;
    float trvled_t;
    float trvled_dist; // distance traveled since last computation
    float trvl_t; // angle at which this distance has been traveled
} robot_t;

typedef struct {
    float x, y;
} point_t;

typedef struct {
    float angle;
    float distance;

    // ========= Read only ========= //

    float x, y;

    lidar_point_type_t type;
} lidar_point_t;

typedef struct {
    float rel_x; // where the beacon is relative to the robot
    float rel_y;
    float dist; // distance and angle to the beacon, as measured by the lidar
    float angle;

    float tolerance; // radius of acceptance, in which any point seen by the lidar is considered as the beacon

    bool lock; // is it successfully being tracked ?
} beacon_t;

typedef struct {
    struct {
        point_t beacons[NUM_BEACONS];
        float x1, y1, x2, y2; // coordinates of the two opposing points (top left and bottom right) of the rectangle defining the playing field
    } field;

    robot_t robot; // coordinates are absolute (to the plating field)
    robot_t adversaries[NUM_ADVERSARIES]; // coordinates are absolute (to the plating field)

    // tolerance follow a linear curve with tolerance = tolerance_coef * value + tolerance_base
    // value is determined by current speed (in both rotation and translation axies)
    float tolerance_coef; // keep in mind that 1 is added to this coeficient, to account for unitialized use (= 0)
    float tolerance_base;

    // ======= Private ======= // (read only, if necessary)

    beacon_t tracked_beacons[NUM_BEACONS]; // coordinates are absolute (to the plating field)

    robot_t prev_robot;
} loc_t;

void setPosition(loc_t* handle, float x, float y, float theta);
void updateField(loc_t* handle, lidar_point_t points[], uint16_t points_nb, uint32_t dt_ms);
void computePosition(loc_t* handle);

#endif /* INC_LOCALIZATION_H_ */
