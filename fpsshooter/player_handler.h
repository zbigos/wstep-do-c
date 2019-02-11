#ifndef PLAYER_HANDLER
    #define PLAYER_HANDLER

    void reserve_wall_memspace(int wallnum);
    void add_wall(float x1, float y1, float x2, float y2);
    void raycaster(struct Point2f* task);
    void rotation_change_setter(double delta);
    void position_change_setter(double delta);
#endif