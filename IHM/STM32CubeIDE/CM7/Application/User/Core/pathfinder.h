#ifndef APPLICATION_USER_CORE_PATHFINDER_H_
#define APPLICATION_USER_CORE_PATHFINDER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SIZE 100

#define MAP_X_SIZE MAP_SIZE
#define MAP_Y_SIZE MAP_SIZE

#define MAX_WAYPOINTS 100


typedef struct {
    uint32_t x, y;

    float dist; // from this point, distance that has to be traveled
    float angle; // from this point, angle to the next one
} instructions_t;

typedef enum {
    empty = 0,
    temp_danger_close = 1, // keep out area around a moving object
    danger_close = 2, // keep out area around a static obstacle
    temp_occupied = 3, // moving object
    occupied = 4, // obstacle
} occupancy_status_t;

typedef enum {
    not_a_part = 0,
    part_of = 1,
    vertex = 2,
    waypoint = 3,
} point_attribute_t;

typedef struct __attribute__((packed)){
    uint16_t value; // distance from origin
    bool visited : 1; // has already been checked

    point_attribute_t path : 3; // is a part of the shortest path

    occupancy_status_t occupancy : 3; // is there an obstacle there ?
} map_element_t;

typedef struct {
    int32_t x, y;
} point_t;

typedef struct { // linked list, each point contains the id of the next one
    int32_t x, y;
    uint16_t next;
} waypoints_t;

typedef struct {
    int32_t curr_x, curr_y;
    int32_t dest_x, dest_y;

    // ============= READ ONLY ============= //

    // general map
    map_element_t map[MAP_Y_SIZE][MAP_X_SIZE];

    // reconnaissance phase (Dijkstra's algorithm)
    point_t candidates[MAP_Y_SIZE * MAP_X_SIZE]; // candidates for the next scan layer
    uint16_t candidates_nb;

    bool path_avail; // at least one path to the destination has been found

    // path's vertices
    waypoints_t waypoints[MAX_WAYPOINTS +1]; // note : index MAX_WAYPOINTS in the next field means there is nothing after this one
    uint16_t waypoints_amnt;

    instructions_t instructions[MAX_WAYPOINTS];
    uint16_t instructions_amnt;
} pathfinder_t;

bool path_process(pathfinder_t* p);
void path_setPos(pathfinder_t* p, int32_t x, int32_t y);
void path_addObstacle(pathfinder_t* p, int32_t x, int32_t y, uint8_t margin);

#endif /* APPLICATION_USER_CORE_PATHFINDER_H_ */
