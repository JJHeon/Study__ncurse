#include "000_ControlCase.h"

#if _016_TESTKEYVALUES

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    int ch = 0;

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    int y = 0;
    while ((ch = getch()) != KEY_F(1)) {
        mvprintw(y++, 0, "Current KEY Value : %5u | can i use this? : %s", ch, has_key(ch) ? "True" : "False");  //has_key는 특수키 리스트에서 사용 가능한지를 판별
        refresh();
    }
    /**
     * RESULT: F11, Tab, Enter 사용불가
     * shift + something 같은 키도 사용 가능
     */
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif