#include <stdio.h>
#include "player_handler.h"

void *keyboard_handler(void *args) {
    while(1) {
        char a = getchar();

        if(a == 'a' || a == 'A') 
            rotation_change_setter(-0.5f);

        if(a == 'd' || a == 'D')
            rotation_change_setter(0.5f);

        if(a == 'w' || a == 'W') 
            position_change_setter(0.1f);

        if(a == 's' || a == 'S')
            position_change_setter(-0.1f);    
    }
}