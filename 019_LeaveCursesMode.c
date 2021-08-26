/** def_prog_mode, reset_prog_mode 사용법 예제
 *  일시적으로 curses 모드 나가기 
 */
#include "000_ControlCase.h"

#if _019_LEAVECURSESMODE

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    printw("Hello World !!!\n");
    refresh();
    sleep(2);
    def_prog_mode();  //curses 모드 나가기
    endwin();

    system("ls");
    sleep(2);
    reset_prog_mode();  //다시 현상태 그대로 불러오기
    refresh();          //if refresh()가 없으면, reset_prog_mode is not work
    sleep(5);

    printw("Another String\n");
    refresh();
    getch();

    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif