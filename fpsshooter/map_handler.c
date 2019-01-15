#include "main.h"
#include <stdio.h>
#include <assert.h>

static int mapsize_x, mapsize_y;
char **map_descriptor;

void read_map_description(char *filename) {
    //FILE *fp;
    //char str[1000];
    
    //fp = fopen(filename, "r");
    //if(fp == NULL)
    //    assert("FILESAVE NOT FOUND");

    //at this point we will have read the map size
        mapsize_x = 10;
        mapsize_y = 10;
        
        map_descriptor = (char**)malloc(sizeof(char *) * mapsize_y);
        for(int i = 0 ; i < mapsize_y; i++)
            map_descriptor[i] = (char*)malloc(sizeof(char) * mapsize_x);

        for(int i = 0 ; i < 5; i++)
            for(int j = 0 ; j < 5; j++)
                map_descriptor[i][j] = 'A';        

    //while(fgets(str, 1000, fp))
    //    printf("%s", str);

    //fclose(fp);
}

void get_map_size(int *x, int *y) {
    *x = mapsize_x;
    *y = mapsize_y;
}
