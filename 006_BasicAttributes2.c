#include "000_ControlCase.h"

#if _006_BASICATTRIBUTES2

#include <stdio.h>

#include <unistd.h>

#include <ncurses.h>

int main(void)
{
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    //GO: attrset 어디까지 유지되는지 비교
    printw("Here");
    refresh();
    sleep(2);

    attron(A_BOLD | A_BLINK);
    mvprintw(1, 0, "attron, This is Bold and blink");
    attroff(A_BOLD | A_BLINK);
    refresh();
    sleep(2);

    attrset(A_UNDERLINE | A_STANDOUT);
    mvprintw(2, 0, "Now attrset, How about that?");
    refresh();
    sleep(2);

    mvprintw(3, 0, "Still continue attrset settings?");
    refresh();
    sleep(2);
    //RESULT: 계속 유지된다. 어떻게 끄냐

    attrset(A_NORMAL);
    mvprintw(4, 0, "A_NORMAL Declare");
    refresh();
    sleep(2);

    attrset(A_ITALIC);
    mvprintw(5, 0, "attrset ITALIC");
    refresh();
    sleep(2);

    standend();
    mvprintw(6, 0, "use standend");
    refresh();
    sleep(2);
    //RESULT: A_NORMAL 또는 standend() 로 일반 모드로 돌아갈 수 있다.
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif