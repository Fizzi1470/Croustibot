#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../Core/pathfinder.h"

#define INITIAL_VAL 65530

#define VERBOSE_PATHFINDER

uint32_t _dist(int32_t x1, int32_t y1, int32_t x2, int32_t y2){return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));}

void path_init(pathfinder_t* p){
    for(uint16_t i = 0; i < MAP_X_SIZE; i++){
        for(uint16_t j = 0; j < MAP_Y_SIZE; j++){
            p->map[j][i].value = INITIAL_VAL;
            p->map[j][i].path = not_a_part;
            p->map[j][i].visited = 0;
        }
    }
    p->path_avail = 0;
    p->waypoints_amnt = 0;
    p->candidates_nb = 0;
}

void path_print(map_element_t map[MAP_Y_SIZE][MAP_X_SIZE]){
    printf("MAP :\n");
    for(uint16_t j = MAP_Y_SIZE -1; j > 0; j--){
        for(uint16_t i = 0; i < MAP_X_SIZE; i++){
            if(map[j][i].occupancy == occupied) printf(" # ");
            else if(map[j][i].occupancy) printf(".%d.", map[j][i].occupancy);
            //else if(map[j][i].path == 4) printf(" a ");
            else if(map[j][i].path == waypoint) printf(" + ");
            else if(map[j][i].path == vertex) printf(" ! ");
            else if(map[j][i].path) printf(" @ ");
            else if(map[j][i].value == INITIAL_VAL) printf(".X.");
            else printf("%0*d", 3, map[j][i].value);
        }
        printf("\n");
    }
    printf("\n");
}

static bool _checkCollision(pathfinder_t* p, int32_t x0, int32_t y0, int32_t x1, int32_t y1){
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        int32_t z;
        z = x0;
        x0 = y0;
        y0 = z;

        z = x1;
        x1 = y1;
        y1 = z;
    }

    if (x0 > x1) {
        int32_t z;
        z = x0;
        x0 = x1;
        x1 = z;

        z = y0;
        y0 = y1;
        y1 = z;
    }

    int32_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int32_t err = dx / 2;
    int32_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0 <= x1; x0++) {
        if (steep) {
            //p->map[x0][y0].path = 4;
            if(p->map[x0][y0].occupancy != empty) return true;
        } else {
            //p->map[y0][x0].path = 4;
            if(p->map[y0][x0].occupancy != empty) return true;
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }

    return false;
}

static void _generateInstructions(pathfinder_t* p){
    uint16_t next_point = 0;
    p->instructions_amnt = 0;
    waypoints_t *current = {0}, *next = {0};

    while(current->next != MAX_WAYPOINTS){
        current = &(p->waypoints[next_point]);
        if(current->next != MAX_WAYPOINTS)
            next = &(p->waypoints[p->waypoints[next_point].next]);
        else
            next = current;

        p->map[current->y][current->x].path = waypoint;

        p->instructions[p->instructions_amnt].x = current->x;
        p->instructions[p->instructions_amnt].y = current->y;

        p->instructions[p->instructions_amnt].dist = _dist(current->x, current->y, next->x, next->y);
        p->instructions[p->instructions_amnt].angle = atan2(next->y - current->y, next->x - current->x);

#ifdef VERBOSE_PATHFINDER
        printf("instruction %d x %d y %d dist %.3f angle %.3f\n", p->instructions_amnt, p->instructions[p->instructions_amnt].x, p->instructions[p->instructions_amnt].y, p->instructions[p->instructions_amnt].dist, p->instructions[p->instructions_amnt].angle);
#endif
        p->instructions_amnt ++;
        next_point = p->waypoints[next_point].next;
    }
}

static void _findShortcuts(pathfinder_t* p){
    for(uint16_t i = 0; i < p->waypoints_amnt -2; i++){ // for each point (except for the last two, as there can't be a shortcut there)
        for(uint16_t j = p->waypoints_amnt -1; j > i +1; j--){ // check all remaining points except for the current one, and the one that's already supposed to be the next, starting from the last one
            if(!_checkCollision(p, p->waypoints[i].x, p->waypoints[i].y, p->waypoints[j].x, p->waypoints[j].y)){ // if we can draw a line between the two points without touching anything
#ifdef VERBOSE_PATHFINDER
                printf("Shortcut ! from %d %d to %d %d (point %d to %d)\n", p->waypoints[i].x, p->waypoints[i].y,p->waypoints[j].x, p->waypoints[j].y, i, j);
#endif

                p->waypoints[i].next = j;
                i = j;
            }
        }
    }

}

/*
static void _findShortcuts(pathfinder_t* p){
    for(uint16_t i = 0; i < p->waypoints_amnt -2; i++){ // for each point (except for the last two, as there can't be a shortcut there)
        uint16_t next_id = p->waypoints[p->waypoints[i].next].next;

        printf("point %d next %d check from %d\n", i,p->waypoints[i].next, next_id);

        while(next_id != MAX_WAYPOINTS) { // draw a line to every other point on the field, forward only
            //printf("checking btwn %d and %d (%d %d ; %d %d)\n", i, next_id, p->waypoints[i].x, p->waypoints[i].y, p->waypoints[next_id].x, p->waypoints[next_id].y);

            if(!_checkCollision(p, p->waypoints[i].x, p->waypoints[i].y, p->waypoints[next_id].x, p->waypoints[next_id].y)){ // if there is no osbtacle in between those two points, link them
                printf("Shortcut ! from %d %d to %d %d (point %d to %d)\n", p->waypoints[i].x, p->waypoints[i].y,p->waypoints[next_id].x, p->waypoints[next_id].y, i, next_id);
                p->waypoints[i].next = next_id; // re-link the point to the one we've just discovered
                i = next_id; // jump all the points in between
                break;
            }

            next_id = p->waypoints[next_id].next;
        }
    }
}
*/

static void _retrace(pathfinder_t* p, int32_t current_x, int32_t current_y, int32_t dest_x, int32_t dest_y, int8_t prev_dx, int8_t prev_dy){
    if(current_x < 0 || current_x >= MAP_X_SIZE || current_y < 0 || current_y >= MAP_Y_SIZE) return;

    //if(p->path_length > 0) p->path[p->path_length -1].next = p->path_length;

    uint16_t shortest_val = -1;
    int32_t shortest_x = 0;
    int32_t shortest_y = 0;
    int8_t next_dx = 0;
    int8_t next_dy = 0;

    /*
    int8_t dx[] = {-1, 0, 1, 0};
    int8_t dy[] = {0, -1, 0, 1};

    for(uint8_t i = 0; i < 4; i++){
        if(!(current_x+dx[i] < 0 || current_x+dx[i] >= MAP_X_SIZE || current_y+dy[i] < 0 || current_y+dy[i] >= MAP_Y_SIZE)){
            int32_t tested_x = current_x + dx[i], tested_y = current_y + dy[i];
            if(tested_x < 0 || tested_x >= MAP_X_SIZE || tested_y < 0 || tested_y >= MAP_Y_SIZE) continue;

            printf("checking %d %d with value %d against value %d\n", tested_x, tested_y, map[tested_y][tested_x].value, shortest_val);
            if(map[tested_y][tested_x].value < shortest_val && !map[tested_y][tested_x].occupied){
                printf("positive\n");
                shortest_val = map[tested_y][tested_x].value;
                shortest_x = tested_x;
                shortest_y = tested_y;
            }
        }
    }
    */

    // go trough a 3x3 square around the visited point, and find the one with the shortest distance
    for(int8_t i = -1; i <= +1; i++){ // go trough x
        for(int8_t j = -1; j <= +1; j++){ // go trough y
            int32_t tested_x = current_x + i, tested_y = current_y + j;
            if(tested_x < 0 || tested_x >= MAP_X_SIZE || tested_y < 0 || tested_y >= MAP_Y_SIZE) continue;
            //printf("checking %d %d with value %d against value %d\n", tested_x, tested_y, map[tested_y][tested_x].value, shortest_val);

            if(p->map[tested_y][tested_x].value < shortest_val && p->map[tested_y][tested_x].occupancy == empty){
                //printf("positive\n");
                shortest_val = p->map[tested_y][tested_x].value;
                shortest_x = tested_x;
                shortest_y = tested_y;
                next_dx = i;
                next_dy = j;
            }

        }
    }

    p->map[current_y][current_x].path = part_of;

    // if direction to the next path point has changed, or if we're come accross the last point (dir 0 0), register this point as a waypoint (a vertex of the path basically)
    if(next_dx != prev_dx || next_dy != prev_dy || (next_dx == 0 && next_dy == 0)) {
        p->waypoints[p->waypoints_amnt].next = p->waypoints_amnt +1;
        p->waypoints[p->waypoints_amnt].x = current_x;
        p->waypoints[p->waypoints_amnt].y = current_y;

        p->map[current_y][current_x].path = vertex;

#ifdef VERBOSE_PATHFINDER
        printf("vertex identified at %d %d (id %d)\n", p->waypoints[p->waypoints_amnt].x, p->waypoints[p->waypoints_amnt].y, p->waypoints_amnt);
#endif

        p->waypoints_amnt++;
    }

     // Then, check if we've arrived at our destination, and end the waypoints linked list
    if(current_x == dest_x && current_y == dest_y){
        p->waypoints[p->waypoints_amnt -1].next = MAX_WAYPOINTS; // this is the last one, consider there is no point linked to this one
        return;
    }

    //printf("---> retraced x %d y %d with value %d\n", shortest_x, shortest_y, shortest_val);
    _retrace(p, shortest_x, shortest_y, dest_x, dest_y, next_dx, next_dy);
}

static void _visit(pathfinder_t* p, int32_t x, int32_t y){
    if(x < 0 || x >= MAP_X_SIZE || y < 0 || y >= MAP_Y_SIZE) return;
    if(p->map[y][x].visited || p->map[y][x].occupancy != empty) return;

    p->map[y][x].visited = true;


    int8_t dx[] = {-1, 0, 1, 0};
    int8_t dy[] = {0, -1, 0, 1};

    for(uint8_t i = 0; i < 4; i++){
        if(!(x+dx[i] < 0 || x+dx[i] >= MAP_X_SIZE || y+dy[i] < 0 || y+dy[i] >= MAP_Y_SIZE)){
            if(p->map[y][x].value +1 < p->map[y + dy[i]][x + dx[i]].value){ // if the path is better (lower distance value), then update
                //printf("placing %d instead of %d at %d %d\n", value, map[j][i].value, i,j);
                p->map[y + dy[i]][x + dx[i]].value = p->map[y][x].value +1; // update the adjecent point's distance
                p->candidates[p->candidates_nb].x = x+dx[i]; // register the adjacent point as a candidate for the next turn
                p->candidates[p->candidates_nb].y = y+dy[i];
                p->candidates_nb ++;
            }
        }
    }

   /*
    // go trough a 3x3 square around the visited point, and determine distances
    for(int32_t i = x-1; i <= x +1; i++){ // go trough x
        for(int32_t j = y-1; j <= y +1; j++){ // go trough y
            if(i < 0 || i >= MAP_X_SIZE || j < 0 || j >= MAP_Y_SIZE) continue;
            if(map[y][x].value +1 < map[j][i].value){ // if the path is better (lower distance value), then update
                //printf("placing %d instead of %d at %d %d\n", value, map[j][i].value, i,j);
                map[j][i].value = map[y][x].value +1; // update the adjecent point's distance
                candidates[candidates_nb].x = i; // register the adjacent point as a candidate for the next turn
                candidates[candidates_nb].y = j;
                candidates_nb ++;
            }
        }
    }
    */
}


bool path_process(pathfinder_t* p){
    path_init(p);

    p->map[p->dest_y][p->dest_y].value = 0;
    _visit(p, p->dest_x, p->dest_y);

    // compute all the distances from the robot to any point on the field
    while(p->candidates_nb != 0){
        //printf("about to start with %d candidates\n", candidates_nb);
        //for (uint16_t i = 0; i < candidates_nb; i++)
        //    printf("candidate %d is x %d y %d\n", i, candidates[i].x, candidates[i].y);
        point_t prev_candidates[p->candidates_nb];
        memcpy(prev_candidates, p->candidates, p->candidates_nb * sizeof(point_t));

        uint16_t prev_candidates_nb = p->candidates_nb;
        p->candidates_nb = 0;

        //printf("candidates %d\n", prev_candidates_nb);
        for(uint16_t i = 0; i < prev_candidates_nb; i++){
            _visit(p, prev_candidates[i].x, prev_candidates[i].y);

            if(prev_candidates[i].x == p->curr_x && prev_candidates[i].y == p->curr_y) p->path_avail = 1; // as we are starting from the end, if we visited our position, that means a path is available

            //printf("visited i %d x %d y %d\n", i, prev_candidates[i].x, prev_candidates[i].y);
        }
    }

    // then, figure out the shortest distance back to the start (by retracing our steps, taking the next lowest adjascent number each time)
    if(p->path_avail){
        _retrace(p, p->curr_x, p->curr_y, p->dest_x, p->dest_y, 0, 0);
#ifdef VERBOSE_PATHFINDER
        printf("waypoints amount %d\n", p->waypoints_amnt);
#endif

        if(p->waypoints_amnt > 2) _findShortcuts(p);

        _generateInstructions(p);

        return 1;
    } else {
        p->instructions_amnt = 0;
        #warning TODO : revert to a very basic movement method
#ifdef VERBOSE_PATHFINDER
        printf("No path available\n");
#endif
        return 0;
    }
}

void path_setPos(pathfinder_t* p, int32_t x, int32_t y){
    if(x < 0 || x >= MAP_X_SIZE || y < 0 || y >= MAP_Y_SIZE) return;

    p->curr_x = x;
    p->curr_y = y;
}

static void _setOccupancy(pathfinder_t* p, int32_t x, int32_t y, occupancy_status_t desired_occupancy){
    if(x < 0 || x >= MAP_X_SIZE || y < 0 || y >= MAP_Y_SIZE) return;
    if(desired_occupancy > p->map[y][x].occupancy) p->map[y][x].occupancy = desired_occupancy;
}

void path_addObstacle(pathfinder_t* p, int32_t x, int32_t y, uint8_t margin){
    int _x = 0;
    int _y = margin;
    int m = 5 - 4 * margin;

    while (_x <= _y){
        for (int xx = x - _y; xx <= x + _y; xx++){
            _setOccupancy(p, xx, y - _x, danger_close);
            _setOccupancy(p, xx, y + _x, danger_close);
        }

        if (m > 0){
            for (int xx = x - _x; xx <= x + _x; xx++){
                _setOccupancy(p, xx, y - _y, danger_close);
                _setOccupancy(p, xx, y + _y, danger_close);
            }

            _y--;
            m -= 8 * _y;
        }

        _x++;
        m += 8 * _x + 4;
    }

    if(x < 0 || x >= MAP_X_SIZE || y < 0 || y >= MAP_Y_SIZE) return;
    p->map[y][x].occupancy = occupied;
}
/*
int main(){

    pathfinder_t path = {
        .dest_x = MAP_X_SIZE -1,
        .dest_y = MAP_Y_SIZE -1,
    };
#ifdef VERBOSE_PATHFINDER
    printf("mem size : 1 point %d, entire map %ld\n", sizeof(map_element_t), sizeof(path.map));
#endif
    path_init(&path);

   srand(time(0));

    // Générer 20 murs aléatoires
    for (int32_t i = 0; i < 20; i++) {
        bool vertical = rand() % 2; // 0 = horizontal, 1 = vertical
        int32_t length = 5 + rand() % 11; // Longueur entre 5 et 15

        int32_t startX = rand() % 50;
        int32_t startY = rand() % 50;

        for (int32_t j = 0; j < length; j++) {
            int32_t x = vertical ? startX : (startX + j) % 50;
            int32_t y = vertical ? (startY + j) % 50 : startY;
            path_addObstacle(&path, x, y, 1);
        }
    }

    path_print(path.map);

    path_setPos(&path, 0, 0);
    path_process(&path);
    path_print(path.map);

    while(path.instructions_amnt){
        path_setPos(&path, path.instructions[1].x, path.instructions[1].y);

        path_process(&path);
        path_print(path.map);
    }

    return 0;
}
*/
