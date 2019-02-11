#include "g_engine.h"
#include "ui.h"
#include <ncurses.h>
#include <pthread.h> 
#include "keyboard_handler.h"
#include "map_handler.h"
#include "main.h"

int term_width = 211;
int term_height = 55;

int main()
{	
    read_map_description("mapa.txt");

	initscr();			/* Start curses mode 		  */
    start_color();

    pthread_t graphical_engine_thread; 
    pthread_create(&graphical_engine_thread, NULL, graphical_engine, NULL); 

    pthread_t ui_thread;
    pthread_create(&ui_thread, NULL, drawUI, NULL);

    pthread_t minimap_thread;
    pthread_create(&minimap_thread, NULL, minimap_renderer, NULL);

    pthread_t env_drawer_thread;
    pthread_create(&env_drawer_thread, NULL, draw_gamearea, NULL);

    pthread_t keyboard_handler_thread;
    pthread_create(&keyboard_handler_thread, NULL, keyboard_handler, NULL);


    pthread_join(graphical_engine_thread, NULL); 
    pthread_join(ui_thread, NULL); 
    pthread_join(minimap_thread, NULL);
    pthread_join(env_drawer_thread, NULL);
    pthread_join(keyboard_handler_thread, NULL);

	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
	return 0;
}