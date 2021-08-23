#include "000_ControlCase.h"

#if _015_TESTFORREFRESH

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    initscr();
    /** 014번에서 refresh를 쓰면 화면 초기화에 대해 테스트로 만듬
     *  Hello world가 지워지면서 Hello world again이 뜨는지 확인하기 위해 작성
     *  RESULT: 문제확인, 아래 테스트코드와는 상관이 없음
     * 문제는 stdscr에 아무것도 출력하지 않은 상태에서,  생성된 window 에서 출력하고 refresh를 호출하면 화면을 초기화한다.
     * 해결책으로 맨 처음에 refresh를 호출해주면되는데, 왜 이런 문제가 생기는 것인지?
     * 생각해보기로 아마 stdscr buffer에 아무것도 없는데 이를 refresh 하면 생기는 문제로 보인다. 만약 무언가 차있으면 그것을 계속 유지하려고 할탠데, 한번도 refresh를 호출하지 않았기 때문에 그 이후에 쓰는 것은 문제가 없을 것임
     */
    /* -----------------------------------------------------------------------------------------------------------------------*/
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // mvprintw(0, 0, "Hello world");
    // refresh();
    // sleep(1);

    // mvprintw(1, 0, "Hello world again");
    // refresh();
    // sleep(1);

    // int x = 0, y = 0;
    // getyx(stdscr, y, x);
    // mvprintw(2, 0, "y: %d, x: %d", y, x);
    // refresh();
    // sleep(1);

    // WINDOW* temp1 = NULL;
    // temp1 = newwin(5, 5, 3, 0);
    // box(temp1, 0, 0);
    // wrefresh(temp1);
    // sleep(1);

    // getyx(stdscr, y, x);
    // mvprintw(8, 0, "y: %d, x: %d", y, x);  //temp1이 그린 box를 무시하고 아까 전에 그렸던 y: %d, x: %d의 마지막 좌표를 표시
    // refresh();
    // sleep(1);

    // int maxy = 0, maxx = 0;
    // getmaxyx(stdscr, maxy, maxx);
    // mvprintw(9, 0, "maxy: %d, maxx: %d", maxy, maxx);  //terminal 최대 크기일 때, maxy : 49, maxx : 188
    // refresh();
    // sleep(1);
    /* -----------------------------------------------------------------------------------------------------------------------*/

    //GO: window를 maxy와 maxx 밖에 출력해보자
    WINDOW* temp2 = NULL;
    temp2 = newwin(5, 5, 45, 0);  //maxy 48 를 넘도록
    box(temp2, 0, 0);
    wrefresh(temp2);
    sleep(1);
    //RESULT: 문제없음
    getch();

    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif