#ifndef MAIN
    #define MAIN
    extern int term_width;
    extern int term_height;

    struct Point2i {
        int x,y;
    };

    struct Point2f {
        float x,y;
    };

    struct Vect2i {
        int dx, dy;
    };

    struct Vect2f {
        float dx, dy;
    };

    struct Line {
        struct Point2i a, b;
    };

    struct Linef {
        struct Point2f a, b;
    };

#endif