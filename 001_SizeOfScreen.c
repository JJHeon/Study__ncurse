#include "000_ControlCase.h"

#if _001_SIZEOFSCREEN

#include <unistd.h>

#include <stdio.h>

#include <ncurses.h>

int main(void)
{
    initscr();
    noecho();

    int max_x = 0;
    int max_y = 0;

    //GO:최대 크기 측정
    getmaxyx(stdscr, max_y, max_x);
    printf("Scr Size : %d %d\n", max_y, max_x);
    //RESULT: Termianl 크기에 따라 가변

    /* -----------------------------------------------------------------------------------------------------------------------*/

    //GO: Win을 하나 더 만들 경우, scr은 어떻게 되나?
    move(0, 0);
    refresh();
    int lines = 30;
    int cols = 30;
    int startline = 0;
    int startcol = 0;
    WINDOW *w1 = NULL;

    w1 = newwin(lines, cols, startline, startcol);
    wrefresh(w1);

    //window w1에 출력
    mvwprintw(w1, 5, 0, "window w1 here");
    wrefresh(w1);

    //stdscr에 출력 살짝 어긋나서
    mvprintw(4, 0, "stdscr here");
    refresh();
    sleep(3);

    //그다음 w1가 겹쳐봄
    mvprintw(5, 0, "stdscr here 2");
    refresh();
    sleep(3);

    //RESULT: WIN1과 STDSCR은 서로 겹친다. 출력물은 한 곳이다.

    /* -----------------------------------------------------------------------------------------------------------------------*/

    endwin();
    return 0;
}

#endif