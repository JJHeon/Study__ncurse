#include "000_ControlCase.h"

#if _030_RESIZETERMINAL

#include <stdio.h>

#include <unistd.h>

#include <ncurses.h>

int main(void) {
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    const char *string = "Boris Johnson has spent decades agitating against the European Union and the last five years battling to free the United Kingdom from the shackles of regulation from Brussels. /* RIGHT */ Now he's in the awkward position of finding himself at the mercy of EU leaders for permission to rejoin an international treaty, or risk devastating Britain's multi-billion-dollar legal services industry.";

    int y = 0, x = 0;
    getmaxyx(stdscr, y, x);
    mvprintw(y - 1, 0, "%s", string);
    mvprintw(0, 0, "Y : %d, X : %d", y, x);
    refresh();

    int aa = is_term_resized(30, 30);
    mvprintw(1, 0, "can? %d", aa);

    refresh();

    resize_term(30, 30);  //RESULT: 이 함수는 현재 커서위치의 window의 크기만을 변경하는 것. termianl 크기가 아님
    refresh();
    sleep(5000);
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif