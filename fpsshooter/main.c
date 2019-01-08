#include "g_engine.h"
#include "ui.h"
#include <ncurses.h>
#include <pthread.h> 

int main()
{	
	initscr();			/* Start curses mode 		  */

    pthread_t graphical_engine_thread; 
    pthread_create(&graphical_engine_thread, NULL, graphical_engine, NULL); 

    pthread_t ui_thread;
    pthread_create(&ui_thread, NULL, drawUI, NULL);


    pthread_join(graphical_engine_thread, NULL); 
    pthread_join(ui_thread, NULL); 

	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
	return 0;
}