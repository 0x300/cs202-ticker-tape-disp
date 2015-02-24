/*****************************************************************************/
/* Josh Lindoo                                                               */
/* Login ID: lind6441                                                        */
/* CS-202, Winter 2015                                                       */
/* Programming Assignment 5                                                  */
/* Ticker Tape Display - Scrolls file contents across terminal               */
/*****************************************************************************/

//includes
#include <stdio.h>
#include <curses.h>

//global declarations


/*****************************************************************************/
/* Function: main                                                            */
/* Purpose:                                                                  */
/* Parameters: int argc, char* argv[]                                        */
/* Returns: int                                                              */
/*****************************************************************************/
int main( int argc, char* argv[] )
{
	printf("Test1\n");
	initscr();
	printw("Test2\n");
	int row, col;
	getmaxyx(stdscr, row, col);
	printw("Test3\n");
	printw("rows = %i, columns = %i\n", row, col);
	printw("Test4\n");
	getch();
	endwin();

	// initscr();			/* Start curses mode 		  */
	// printw("Hello World !!!");	/* Print Hello World		  */
	// refresh();			/* Print it on to the real screen */
	// getch();			/* Wait for user input */
	// endwin();			/* End curses mode		  */

    return 0;
}