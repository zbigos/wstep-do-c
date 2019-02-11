#include <stdio.h>
#include "main.h"
#include <math.h>
#include <stdlib.h>

#define FOV 0.25f
#define PI 3.1415f
#undef GENGINE_DEBUG

float min(float a, float b) {
    return a>b?b:a;
}

float max(float a, float b) {
    return a<b?b:a;
}
static float player_x_pos = 0.0f;
static float player_y_pos = 0.0f;
static float rotation = 0.0f;

static struct Linef *walls;
static int next_wall = 0;
static int wall_limit = 0;

void reserve_wall_memspace(int wallnum) {
    walls = (struct Linef*)malloc(wallnum * sizeof(struct Linef*));
    wall_limit = wallnum;
}

void add_wall(float x1, float y1, float x2, float y2) {
    walls[next_wall].a.x = x1;
    walls[next_wall].a.y = y1;
    walls[next_wall].b.x = x2;
    walls[next_wall].b.y = y2;
    next_wall++;
}

float FOV_sanitizer(float a) {
    if(a > 20.0)
        return 1.0;

    return 20.0-a;
}

double collider(struct Linef cast, struct Linef wall) {
    // cast.a is the player position
    // A, B, C, D
    struct Point2f A = cast.a;
    struct Point2f B = cast.b;
    struct Point2f C = wall.a;
    struct Point2f D = wall.b;
    
    float a1 = B.y - A.y;
    float b1 = A.x - B.x;
    float c1 = a1*A.x + b1*A.y;

    float a2 = D.y - C.y;
    float b2 = C.x - D.x;
    float c2 = a2*C.x + b2*C.y;

    float det = a1*b2 - a2*b1;

    #ifdef GENGINE_DEBUG
        fprintf(stderr, ">> <%lf %lf> <%lf %lf> ", C.x, C.y, D.x, D.y);
    #endif

    if(abs(det) <= 0.1f) {
        return -1.0;
    }

    float xhit = (b2*c1 - b1*c2)/det;
    float yhit = (a1*c2 - a2*c1)/det;
    
    #ifdef GENGINE_DEBUG
        fprintf(stderr, "%lf %lf\n\r", xhit, yhit);
    #endif

    if(min(A.x, B.x) <= xhit && xhit <= max(A.x, B.x))
        if(min(A.y, B.y) <= yhit && yhit <= max(A.y, B.y))
            if(min(C.x, D.x) <= xhit && xhit <= max(C.x, D.x))
                if(min(C.y, D.y) <= yhit && yhit <= max(C.y, D.y))
                    return ((A.x - xhit) * (A.x - xhit) + (A.y - yhit) * (A.y - yhit))/3.0;

    return -1.0f;
}

void rotation_change_setter(double delta) {
    rotation += delta;
}

void position_change_setter(double delta) {
    player_x_pos += delta*cos(rotation*PI/180.0f);
    player_y_pos += delta*sin(rotation*PI/180.0f);
}

void raycaster(struct Point2f* task) {
    struct Linef cast;
    struct Point2f ppoz;
    ppoz.x = player_x_pos;
    ppoz.y = player_y_pos;
    cast.a = ppoz;
    for(int i = 0 ; i < term_width; i++) { 
        double angle = (double)((int)(rotation + (i-term_height/2)*FOV + 360.0f) % 360);
        
        #ifdef GENGINE_DEBUG 
            fprintf(stderr, "%lf ", angle); 
        #endif
        // jestem na pozycji playser_x_pos, player_y_pos, i paczę w strony angle
        struct Point2f endpoz;
        endpoz.x = 2137.0f*cos(angle*PI/180.0) + player_x_pos;
        endpoz.y = 2137.0f*sin(angle*PI/180.0) + player_y_pos;
        cast.b = endpoz;
        #ifdef GENGINE_DEBUG 
            fprintf(stderr, "%lf %lf ", endpoz.x, endpoz.y);
        #endif
        double mindist = 10000.0f;
        double lookup = -1.0f;
        for(int j = 0 ; j < next_wall; j++) {
            double collision_dist = collider(cast, walls[j]);
            if(collision_dist > 0.0f && collision_dist < mindist) {
                mindist = collision_dist;
                lookup = j;
            }
        }
        
        #ifdef GENGINE_DEBUG 
            fprintf(stderr, "%lf\n\r", mindist);
        #endif
        task[i].x = FOV_sanitizer(mindist);
        task[i].y = lookup;
    }
}