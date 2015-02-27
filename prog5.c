/*****************************************************************************/
/* Josh Lindoo                                                               */
/* Login ID: lind6441                                                        */
/* CS-202, Winter 2015                                                       */
/* Programming Assignment 5                                                  */
/* Ticker Tape Display - Scrolls file contents across terminal               */
/*****************************************************************************/

//includes
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <curses.h>
#include <getopt.h>

//global declarations
int row, col = 0; //current row, col
int numRows, numCols; //number of rows, cols
int maxCharsToPrint = 1; //max number of characters to print to window
int leftTruncate = 0; //chars to truncate from left side of the screen
int msDelay = 1000; //default delay between scrolling
char *fileBuffer; //file buffer to be dynamically allocated later
long fileSize; //size of input file
char *fileName; //name of input file

//global options
int loopMode = 0; //en for loop mode

/*****************************************************************************/
/* Function: scrollMessage                                                   */
/* Purpose: display the message on the screen                                */
/* Parameters: int signum                                                    */
/* Returns: void                                                             */
/*****************************************************************************/
void scrollMessage(int signum)
{
    signal(SIGALRM, scrollMessage); //reset signal binding jic

    mvprintw(row, col-1, "%.*s", maxCharsToPrint, fileBuffer + leftTruncate);

    if(col-1 != 0)
    {
        col--;
    }
    else if(leftTruncate < fileSize)
    {
        leftTruncate++;
    }

    if(maxCharsToPrint < numCols) maxCharsToPrint++;

    if(leftTruncate == fileSize)
    {
        if(loopMode)
        {
            //reset everything
            col = numCols;
            leftTruncate = 0;
            maxCharsToPrint = 1;
        }
        else
        {
            endwin();
            exit(0);
        }
    }

    refresh();
}

/*****************************************************************************/
/* Function: setTicker                                                       */
/* Purpose: set alarm time                                                   */
/* Parameters: int n_msecs                                                   */
/* Returns: int                                                              */
/*****************************************************************************/
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
/* Purpose: handle args, start ticker tap                                    */
/* Parameters: int argc, char* argv[]                                        */
/* Returns: int                                                              */
/*****************************************************************************/
int main( int argc, char* argv[] )
{
    //handle options/args
    int opt; //option to handle
    while ((opt = getopt(argc, argv, "t:l")) != -1) {
        switch (opt) {
            case 't':
                //manual delay time
                msDelay = atoi(optarg);
                break;
            case 'l':
                //enable looping
                loopMode = 1;
                break;
            default:
                break;
        }
    }

    //handle one arg after processing options
    if(argv[optind] == NULL)
    {
        printf("Need to provide filename..\n");
        exit(0);
    }

    FILE *file = fopen(argv[optind], "r"); //open the file for reading
    fseek(file, 0, SEEK_END); //seek to end
    fileSize = ftell(file); //store the end pos as file size
    rewind(file); //back to the start

    fileBuffer = malloc(fileSize+1);
    fread(fileBuffer, fileSize, 1, file); //read whole file
    fclose(file);
    // printf("file size: %d\n", fsize);
    
    initscr();
    curs_set(0); //no curser
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

    return 0;
}