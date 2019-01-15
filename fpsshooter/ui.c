#include <stdio.h>
#include "g_engine.h"
#include "main.h"

#define ABOMICNACJA(XCORD, YCORD, BITMASK) \
    do {    \
        if(BITMASK & 1) a->charactermap[XCORD+7][YCORD].chr = '#'; else a->charactermap[XCORD+7][YCORD].chr = ' ';   \
        if(BITMASK & 2) a->charactermap[XCORD+6][YCORD+1].chr = '#'; else a->charactermap[XCORD+6][YCORD+1].chr = ' '; \
        if(BITMASK & 4) a->charactermap[XCORD+4][YCORD+1].chr = '#'; else a->charactermap[XCORD+4][YCORD+1].chr = ' ';  \
        if(BITMASK & 8) a->charactermap[XCORD+3][YCORD].chr = '#'; else a->charactermap[XCORD+3][YCORD].chr = ' '; \
        if(BITMASK & 16) a->charactermap[XCORD+4][YCORD-1].chr = '#'; else a->charactermap[XCORD+4][YCORD-1].chr = ' '; \
        if(BITMASK & 32) a->charactermap[XCORD+6][YCORD-1].chr = '#'; else a->charactermap[XCORD+6][YCORD-1].chr = ' '; \
        if(BITMASK & 64) a->charactermap[XCORD+5][YCORD].chr = '#'; else a->charactermap[XCORD+5][YCORD].chr = ' '; \
        if((BITMASK & 1) + (BITMASK & 32)) a->charactermap[XCORD+7][YCORD-1].chr = '#'; else a->charactermap[XCORD+7][YCORD-1].chr = ' ';  \
        if((BITMASK & 1) + (BITMASK & 2)) a->charactermap[XCORD+7][YCORD+1].chr = '#'; else a->charactermap[XCORD+7][YCORD+1].chr = ' ';   \
        if((BITMASK & 16) + (BITMASK & 8)) a->charactermap[XCORD+3][YCORD-1].chr = '#'; else a->charactermap[XCORD+3][YCORD-1].chr = ' ';  \
        if((BITMASK & 4) + (BITMASK & 8)) a->charactermap[XCORD+3][YCORD+1].chr = '#'; else a->charactermap[XCORD+3][YCORD+1].chr = ' ';   \
        if((BITMASK & 64) + (BITMASK & 2) + (BITMASK & 64) + (BITMASK & 4) + (BITMASK & 4) + (BITMASK & 2)) a->charactermap[XCORD+5][YCORD+1].chr = '#'; else a->charactermap[XCORD+5][YCORD+1].chr = ' '; \
        if((BITMASK & 64) + (BITMASK & 32) + (BITMASK & 64) + (BITMASK & 16) + (BITMASK & 16) + (BITMASK & 32)) a->charactermap[XCORD+5][YCORD-1].chr = '#'; else a->charactermap[XCORD+5][YCORD-1].chr = ' '; \
    } while(0)


int decode(int number) {
    // i am so very ashamed about this
    //    1
    //32     2 
    //   64 
    //16     4
    //    8

    switch (number) {
        case 0: return ((1 * 1)|(2 * 1)|(4 * 1)|(8 * 1)|(16 * 1)|(32 * 1)|(64 * 0));
        case 1: return ((1 * 0)|(2 * 1)|(4 * 1)|(8 * 0)|(16 * 0)|(32 * 0)|(64 * 0));
        case 2: return ((1 * 1)|(2 * 1)|(4 * 0)|(8 * 1)|(16 * 1)|(32 * 0)|(64 * 1));
        case 3: return ((1 * 1)|(2 * 1)|(4 * 1)|(8 * 1)|(16 * 0)|(32 * 0)|(64 * 1));
        case 4: return ((1 * 0)|(2 * 1)|(4 * 1)|(8 * 0)|(16 * 0)|(32 * 1)|(64 * 1));
        case 5: return ((1 * 1)|(2 * 0)|(4 * 1)|(8 * 1)|(16 * 0)|(32 * 1)|(64 * 1));
        case 6: return ((1 * 0)|(2 * 0)|(4 * 1)|(8 * 1)|(16 * 1)|(32 * 1)|(64 * 1));
        case 7: return ((1 * 1)|(2 * 1)|(4 * 1)|(8 * 0)|(16 * 0)|(32 * 0)|(64 * 0));
        case 8: return ((1 * 1)|(2 * 1)|(4 * 1)|(8 * 1)|(16 * 1)|(32 * 1)|(64 * 1));
        case 9: return ((1 * 1)|(2 * 1)|(4 * 1)|(8 * 0)|(16 * 0)|(32 * 1)|(64 * 1));
    }

    // -O3 will take care of this mess anyway
}

void *minimap_renderer(void *args) {
    struct Gsprite *a = register_draw_area(term_width-40, term_height-20, 40,20,100,false);
    for(int i = 0 ; i < 40; i++)
        for(int j = 0 ; j < 20; j++)
            a->charactermap[j][i].chr = 'O';
    
}

void *drawUI(void *args) {
    //first we register a render window
    int bottom_bar_height = 10;
    struct Gsprite *a = register_draw_area(0, 0, term_width, term_height, 0, false);
    for(int i = 0 ; i < term_height; i++)
        for(int j = 0 ; j < term_width; j++)
            a->charactermap[i][j].chr = 0;
  
    for(int i = 0 ; i < term_height; i++) {
        a->charactermap[i][0].chr = '#';
        a->charactermap[i][term_width-1].chr = '#';
    }

        for(int i = 0 ; i < term_width; i++) {
        a->charactermap[0][i].chr = '#';
        a->charactermap[term_height-1][i].chr = '#';
    }
    
    for(int i = 0 ; i < term_width-40; i++) {
        a->charactermap[term_height-bottom_bar_height][i].chr = '#';
    }
    
    for(int i = term_width-40; i < term_width; i++) {
        a->charactermap[term_height-20][i].chr = '#';
    }
    
    for(int i = term_height-20 ; i < term_height; i++) {
        a->charactermap[i][term_width-40].chr = '#';
    }
    
    int hp = 999;
    while(1) {
        int anger = 10;

        //print out the HEALTH bar
        int HP_text_location_from_left = 10;
        char HP_text[6] = "HEALTH";
        for(int i = 0 ; i < 6; i++)
            a->charactermap[term_height-bottom_bar_height+1][HP_text_location_from_left+i].chr = HP_text[i];
        int mask = decode(8);
        hp--;
        if(hp == 0)
            hp = 999;
            
        if( hp >= 100 ) {
        ABOMICNACJA(term_height-bottom_bar_height, HP_text_location_from_left-3, decode(hp/100));
        ABOMICNACJA(term_height-bottom_bar_height, HP_text_location_from_left+1, decode((hp/10)%10));
        ABOMICNACJA(term_height-bottom_bar_height, HP_text_location_from_left+5, decode(hp%10));
        } else if (hp >= 10) {
        ABOMICNACJA(term_height-bottom_bar_height, HP_text_location_from_left-3, decode((hp/10)%10));
        ABOMICNACJA(term_height-bottom_bar_height, HP_text_location_from_left+1, decode(hp%10));    
        } else {
        ABOMICNACJA(term_height-bottom_bar_height, HP_text_location_from_left-3, decode(hp%10));    
        }

    //    1
    //32     2 
    //   64 
    //16     4
    //    8
    }

    //HP
    //AMMO
    //ANGER
   
}