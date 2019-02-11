#include "main.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "map_handler.h"
#include "player_handler.h"
#include <stdlib.h>

static int mapsize_x, mapsize_y;
static char **map_descriptor;

struct map_info_t getmap() {
    struct map_info_t ret;
    ret.mapsize_x = mapsize_x;
    ret.mapsize_y = mapsize_y;
    
    ret._map_descriptor = (char**)malloc(sizeof(char *) * mapsize_y);
    for(int i = 0 ; i < mapsize_y; i++)
        ret._map_descriptor[i] = (char*)malloc(sizeof(char) * mapsize_x);
    for(int i = 0 ; i < mapsize_x; i++)
        for(int j = 0 ; j < mapsize_y; j++)
            ret._map_descriptor[i][j] = map_descriptor[i][j];
    return ret;
}

void read_map_description(char *filename) {
    FILE *fp;
    char str[1000];
    
    fp = fopen(filename, "r");
    //if(fp == NULL)
    //    assert("MAPFILE NOT FOUND");

    fgets(str, 1000, fp);
    mapsize_x = atoi(str);
    fgets(str, 1000, fp);
    mapsize_y = atoi(str);

    map_descriptor = (char**)malloc(sizeof(char *) * mapsize_y);
    for(int i = 0 ; i < mapsize_y; i++)
        map_descriptor[i] = (char*)malloc(sizeof(char) * mapsize_x);

    reserve_wall_memspace(mapsize_x * mapsize_y * 5);

    for(int i = 0 ; i < mapsize_x; i++) {
        fgets(str, 1000, fp);
        for(int j = 0 ; j < mapsize_y; j++)
            map_descriptor[i][j] = str[j];
        }

//poziome

    for(int i = 0 ; i < mapsize_x-1; i++)
        for(int j = 0 ; j < mapsize_y; j++)
            if(map_descriptor[i][j] != 'O' && map_descriptor[i+1][j] == 'O')
                add_wall((float)i+2.0f, (float)j, (float)i+2.0f, (float)j+1.0f); // górne boki

    for(int i = 1 ; i < mapsize_x; i++)
        for(int j = 0 ; j < mapsize_y; j++)
            if(map_descriptor[i][j] != 'O' && map_descriptor[i-1][j] == 'O')
                add_wall((float)i+3.0f, (float)j, (float)i+3.0f, (float)j+1.0f); //dolne boki

//pionowe

    for(int i = 0 ; i < mapsize_x; i++)
        for(int j = 0 ; j < mapsize_y-1; j++)
            if(map_descriptor[i][j] != 'O' && map_descriptor[i][j+1] == 'O')
                add_wall((float)i+2.0f, (float)j+1.0f, (float)i+3.0f, (float)j+1.0f); // prawe boki

    for(int i = 0 ; i < mapsize_x; i++)
        for(int j = 1 ; j < mapsize_y; j++)
            if(map_descriptor[i][j] != 'O' && map_descriptor[i][j-1] == 'O')
                add_wall((float)i+2.0f, (float)j, (float)i+3.0f, (float)j); // lewe boki


    fclose(fp);
}

void get_map_size(int *x, int *y) {
    *x = mapsize_x;
    *y = mapsize_y;
}
