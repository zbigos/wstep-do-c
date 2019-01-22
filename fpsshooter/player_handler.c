#include <stdio.h>
#include "main.h"
#include <math.h>
#include <stdlib.h>

#define FOV 0.1f
#define PI 3.1415f

static float player_x_pos = 0.0f;
static float player_y_pos = 0.0f;
static float rotation = 0.0f;

static struct Linef **walls;
static int next_wall = 0;
static int wall_limit = 0;

void reserve_wall_memspace(int wallnum) {
    walls = (struct Linef**)malloc(wallnum * sizeof(struct Linef*));
    wall_limit = wallnum;
}

void add_wall(float x1, float y1, float x2, float y2) {
    walls[next_wall]->a.x = x1;
    //walls[next_wall]->a.y = y1;
    //walls[next_wall]->b.x = x2;
    //walls[next_wall]->b.y = y2;
    next_wall++;
}


void raycaster() {
    struct Linef cast;
    struct Point2f ppoz;
    ppoz.x = player_x_pos;
    ppoz.y = player_y_pos;
    cast.a = ppoz;
    
    for(int i = 0 ; i < term_width; i++) { 
        double angle = rotation + ((int)((i-term_height/2)*FOV + 360.0f) % 360);
        // jestem na pozycji playser_x_pos, player_y_pos, i paczę w strony angle
        struct Point2f endpoz;
        endpoz.x = 2137.0f*cos(angle*PI/180.0);
        endpoz.y = 2137.0f*sin(angle*PI/180.0);
        cast.b = endpoz;
    }
}