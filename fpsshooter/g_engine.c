#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <ncurses.h>
#include <stdlib.h>
#include "g_engine.h"
#define GENGINE_MAXIMUM_SPRITES 128

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

static struct Gsprite sprite_array[GENGINE_MAXIMUM_SPRITES];
static int next_gsprite_position = 0;
static int sprite_array_baked = 1;

void bake_sprite_array(void) {
    return;
}

struct Gsprite *register_draw_area(int start_horisontal, int start_vertical, int horisontal, int vertical, int priority, bool bake) {
    if (next_gsprite_position+1 >= GENGINE_MAXIMUM_SPRITES) {
        return NULL;
    }
    
    struct Gsprite *a = (struct Gsprite*)malloc(sizeof(struct Gsprite));
    a->start_horisontal_position = start_horisontal;
    a->start_vertical_position = start_vertical;
    a->horisontal_size = horisontal;
    a->vertical_size = vertical;
    a->priority = priority;

    a->charactermap = (struct Pixel**)malloc(sizeof(struct Pixel*) * vertical);
    for(int i = 0 ; i < vertical; i++)
        a->charactermap[i] = (struct Pixel*)malloc(sizeof(struct Pixel) * horisontal);

    sprite_array[next_gsprite_position] = *a;

    next_gsprite_position++;

    if (bake) {
        bake_sprite_array();
    }

    return a;
}

int get_avg_ms_cnt(void) {
    return 0;
}

static int show_fps_meter = 1;
void show_fps_meter_setter(int value) {
    show_fps_meter = value;
    return;
}

void* graphical_engine(void *args) {
    while(1) {
        long long int time_start = current_timestamp();
        for(int i = 0 ; i < next_gsprite_position; i++) {
            for(int j = 0 ; j < (sprite_array[i].vertical_size); j++)
               for(int k = 0 ; k < (sprite_array[i].horisontal_size); k++)
                    if(sprite_array[i].charactermap[j][k].chr >= 10)
                        mvprintw(j, k, "%c", sprite_array[i].charactermap[j][k].chr);
        }

        refresh();
    }
}