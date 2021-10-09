#include "000_ControlCase.h"

#if _031_RESIZETERMINAL2

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <ncurses.h>

int main(void) {
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    WINDOW *ventana1;

    int max_y = 0, max_x = 0;
    int ret = 0;
    int a = 0;

    /* Settings */
    start_color();
    ventana1 = newwin(15, 50, 0, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_YELLOW);
    wbkgd(ventana1, COLOR_PAIR(1));
    //wrefresh(ventana1);
    refresh();
    getch();

    /* Resize 상황 1 */
    a = 0, ret = 0;
    ret = system("resize -s 20 20");
    a = WEXITSTATUS(ret);  //return 1을 주는데.. 이 값은 error
    mvprintw(3, 0, "%d", a);
    refresh();
    getch();
    getch();

    mvwprintw(ventana1, 0, 0, "Resize 20-20|First");
    getmaxyx(stdscr, max_y, max_x);
    mvwprintw(ventana1, 1, 0, "stdscr | Max Y : %d | Max X : %d", max_y, max_x);
    getmaxyx(ventana1, max_y, max_x);
    mvwprintw(ventana1, 2, 0, "ventan | Max Y : %d | Max X : %d", max_y, max_x);
    wrefresh(ventana1);
    refresh();
    //sleep(4);
    //wgetch(ventana1);
    getch();
    getch();

    /* Resize 상황 2 */
    system("resize -s 35 85");
    wbkgd(ventana1, COLOR_PAIR(2));
    mvwprintw(ventana1, 0, 0, "Resize 35-85|Second");
    getmaxyx(stdscr, max_y, max_x);
    mvwprintw(ventana1, 1, 0, "stdscr | Max Y : %d | Max X : %d", max_y, max_x);
    getmaxyx(ventana1, max_y, max_x);
    mvwprintw(ventana1, 2, 0, "ventan | Max Y : %d | Max X : %d", max_y, max_x);
    wrefresh(ventana1);
    refresh();
    //sleep(4);
    //wgetch(ventana1);
    getch();
    getch();

    /* Resize 상황 3 */
    system("resize -s 100 100");
    wbkgd(ventana1, COLOR_PAIR(1));
    mvwprintw(ventana1, 0, 0, "Resize 100-100|Third");
    getmaxyx(stdscr, max_y, max_x);
    mvwprintw(ventana1, 1, 0, "stdscr | Max Y : %d | Max X : %d", max_y, max_x);
    getmaxyx(ventana1, max_y, max_x);
    mvwprintw(ventana1, 2, 0, "ventan | Max Y : %d | Max X : %d", max_y, max_x);
    wrefresh(ventana1);
    refresh();
    //sleep(4);
    //wgetch(ventana1);
    getch();

    getch();

    /* Resize 상황 4 */
    system("clear");
    wbkgd(ventana1, COLOR_PAIR(2));
    mvwprintw(ventana1, 0, 0, "Clear system call|Quad");
    getmaxyx(stdscr, max_y, max_x);
    mvwprintw(ventana1, 1, 0, "stdscr | Max Y : %d | Max X : %d", max_y, max_x);
    getmaxyx(ventana1, max_y, max_x);
    mvwprintw(ventana1, 2, 0, "ventan | Max Y : %d | Max X : %d", max_y, max_x);
    wrefresh(ventana1);
    refresh();
    //sleep(4);
    //wgetch(ventana1);
    getch();

    delwin(ventana1);
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif