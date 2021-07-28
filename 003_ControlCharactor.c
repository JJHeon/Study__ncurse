#include "000_ControlCase.h"

#if _003_CONTROLCHARACTOR

#include <stdio.h>

#include <unistd.h>

#include <ncurses.h>

int main(void)
{
    initscr();
    noecho();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    //GO: 글자 폰트변경 및 확인
    const char ct = 'F';
    mvaddch(0, 0, ct);
    refresh();
    mvaddch(1, 0, ct | A_BOLD | A_UNDERLINE);
    refresh();
    mvaddch(2, 0, ct | A_STANDOUT);
    refresh();
    mvaddch(3, 0, ct | A_REVERSE);
    refresh();
    mvaddch(4, 0, ct | A_BLINK);
    refresh();
    mvaddch(5, 0, ct | A_UNDERLINE);
    refresh();
    mvaddch(6, 0, ct | A_VERTICAL);
    refresh();
    mvaddch(7, 0, ct | A_HORIZONTAL);
    refresh();
    mvaddch(8, 0, ct | A_TOP);
    refresh();
    mvaddch(9, 0, ct | A_PROTECT);
    refresh();
    mvaddch(10, 0, ct | A_NORMAL);
    refresh();
    mvaddch(11, 0, ct | A_ITALIC);
    refresh();
    mvaddch(12, 0, ct | A_RIGHT);
    refresh();
    mvaddch(13, 0, ct | A_LEFT);
    refresh();
    mvaddch(14, 0, ct | A_INVIS);
    refresh();
    mvaddch(15, 0, ct | A_COLOR);
    refresh();
    mvaddch(16, 0, ct | A_DIM);
    refresh();
    mvaddch(17, 0, ct | A_ALTCHARSET);
    refresh();
    mvaddch(18, 0, ct | A_ATTRIBUTES);
    refresh();
    sleep(3);
    //RESULT:

    /* -----------------------------------------------------------------------------------------------------------------------*/

    //GO: mvaddnstr은?
    const char *string = "Hello world";
    mvaddstr(19, 0, string);
    refresh();
    mvaddnstr(20, 0, string, 7);
    refresh();
    mvaddnstr(21, 0, string, -1);
    refresh();
    sleep(3);
    //RESUL1T: mvaddnstr 는 n만큼만 출력, n이 음수일 경우 모두 출력

    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif