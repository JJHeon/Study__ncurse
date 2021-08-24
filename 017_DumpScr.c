/** scr_dump(), scr_restore()
 * 
 */
#include "000_ControlCase.h"

#if _017_DUMPSCR

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    initscr();
    refresh();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    int current_y = 0, current_x = 0;
    int ch = 0;

    noecho();
    keypad(stdscr, TRUE);
    mvprintw(1, 0, "Wirting Everything here : ");
    refresh();

    while ((ch = getch()) != KEY_F(1)) {
        if (ch == 10) {  //Enter == 10 == carrage return //리눅스에서는 carrage return을 허용하지만 \n은 안함, 새로줄은 리눅스에선 \n, window에선 \r\n
            addch('\n');
        } else {
            addch(ch);
        }
        getyx(stdscr, current_y, current_x);
        mvprintw(0, 0, "Last cursor : Y:%3d | X:%3d", current_y, current_x);
        move(current_y, current_x);  //cursor move
        refresh();
    }

    sleep(2);
    if (OK == scr_dump("dump.txt")) {  //file을 system call로 생성하지 않아도 자동으로 파일을 만듬, 기존 파일 존재시 덮어씌우기
        mvprintw(30, 0, "Success");
    } else {
        mvprintw(30, 0, "fail");
    }
    refresh();
    sleep(2);

    scr_restore("dump2.txt");  //dump2는 다른 dump을 복사해둔 과거파일
    refresh();                 //scr_restore 후, refresh를 하지 않으면 출력이 안됨, 그리고 scr_dump호출까지만 화면저장. Success나 Fail은 X
    sleep(2);
    getch();

    /* -----------------------------------------------------------------------------------------------------------------------*/

    endwin();
    return 0;
}

#endif