/*****************************************************************************/
/* Josh Lindoo                                                               */
/* Login ID: lind6441                                                        */
/* CS-202, Winter 2015                                                       */
/* Programming Assignment 5                                                  */
/* Ticker Tape Display - Scrolls file contents across terminal               */
/*****************************************************************************/

//includes
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <curses.h>

//global declarations
int row, col = 0; //current row, col
int numRows, numCols; //number of rows, cols
int msDelay = 1000; //default delay between scrolling


void scrollMessage(int signum)
{
    signal(SIGALRM, scrollMessage); //reset signal binding jic

    move(row,col);
    addstr("X");
    col++;
    refresh();
}

//utility copied directly from textbook
int setTicker( int n_msecs )
{
    struct itimerval new_timeset; //creating new struct itimerval to set the timer
    long n_sec, n_usecs; //for calculations of seconds and microseconds

    n_sec = n_msecs / 1000;
    n_usecs = ( n_msecs % 1000 ) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;
    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

/*****************************************************************************/
/* Function: main                                                            */
/* Purpose:                                                                  */
/* Parameters: int argc, char* argv[]                                        */
/* Returns: int                                                              */
/*****************************************************************************/
int main( int argc, char* argv[] )
{
    
    
    initscr();
    crmode();
    noecho();
    clear();

    getmaxyx(stdscr, numRows, numCols); //can only use after initscr()
    col = numCols; //start in right corner of window
    
    signal(SIGALRM, scrollMessage);
    if(setTicker(msDelay) == -1)
    {
        perror("setTicker");
    }
    else
    {
        while(1)
        {
            pause();
        }
    }

    endwin();

    return 0;
}