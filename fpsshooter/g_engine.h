#ifndef G_ENGINE
    #define G_ENGINE

    #include <stdbool.h>
    struct Pixel {
        int chr;
    };

    //count from top left corner
    struct Gsprite {
        struct Pixel **charactermap;
        int start_horisontal_position;
        int start_vertical_position;
        int horisontal_size;
        int vertical_size;
        int priority;
    };

    void* graphical_engine(void *args);
    struct Gsprite *register_draw_area(int start_horisontal, int start_vertical, int horisontal, int vertical, int priority, bool bake);
#endif