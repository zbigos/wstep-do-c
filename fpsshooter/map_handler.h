#ifndef MAP_HANDLER
    #define MAP_HANDLER
    struct map_info_t {
        int mapsize_x;
        int mapsize_y;
        char **_map_descriptor;
    };
  
    void read_map_description(char *filename);
    struct map_info_t getmap();
#endif