#include "000_ControlCase.h"

#if _002_OUTOFBOUNDERY

#include <stdio.h>

#include <unistd.h>

#include <ncurses.h>

int main(void)
{

    initscr();
    noecho();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    //GO: 만약 Termianl 크기 밖에서 출력하면 어떻게 반응할 것인가?, Terminal에 드래그할 수 있도록 만드는가?
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);
    mvprintw(max_y - 1, 0, "MAX LINE");
    refresh();
    sleep(3);
    mvprintw(max_y + 5, max_x + 5, "Hello Here!");
    refresh();
    sleep(3);
    //RESULT: max line을 넘어간 것은 출력되지 않음.
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif
