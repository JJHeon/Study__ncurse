/** putwin(), getwin(), copywin()에 대해
 * 
 */
#include "000_ControlCase.h"

#if _018_DUMPWIN

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    initscr();

    refresh();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    int scr_max_y = 0, scr_max_x = 0;
    getmaxyx(stdscr, scr_max_y, scr_max_x);

    WINDOW* window1 = newwin(10, scr_max_x, 1, 0);
    WINDOW* window2 = newwin(5, scr_max_x, 11, 0);

    mvprintw(0, 0, "Size of Screen | Y : %3d, X : %3d", scr_max_y, scr_max_x);
    box(window1, 0, 0);
    box(window2, 0, 0);
    wrefresh(window1);
    wrefresh(window2);
    refresh();
    getch();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif