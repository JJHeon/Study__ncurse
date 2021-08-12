#include "000_ControlCase.h"

#if _012_QUESTIONFORWGETCH

#include <stdio.h>

#include <unistd.h>

#include <ncurses.h>

int main(void)
{
    initscr();
    /**
     * GO:0 복수의 window가 있을 때, wgetch는 어떻게 처리되는가?
     */
    /* -----------------------------------------------------------------------------------------------------------------------*/

    WINDOW *sample1, *sample2, *sample3;
    int s1_startx = 0, s1_starty = 0, s2_startx = 0, s2_starty = 20, s3_startx = 0, s3_starty = 32;
    int s1_sizex = 20, s1_sizey = 4, s2_sizex = 30, s2_sizey = 10, s3_sizex = 30, s3_sizey = 10;
    int ch = 0;

    noecho();        //사용할지 말지로 wgetch의 이유 확인가능
    curs_set(FALSE); //curse off
    cbreak();

    sample1 = newwin(s1_sizey, s1_sizex, s1_starty, s1_startx);
    sample2 = newwin(s2_sizey, s2_sizex, s2_starty, s2_startx);
    sample3 = newwin(s3_sizey, s3_sizex, s3_starty, s3_startx);

    box(sample1, 0, 0);
    box(sample2, 0, 0);
    box(sample3, 0, 0);

    wrefresh(sample1);
    wrefresh(sample2);
    wrefresh(sample3);

    /**
     * Keypad는 유저 터미널 키패드를 enable 시킨다.
     * enable되면 wgetch는 function key를 반환 (KEY_LEFT 같은), false인 경우 function key를 해석하지 않는다.
     * 이 옵션이 켜져있는 경우 wgetch 가 불렸을때, 터미널 키패드를 켜지게 만든다.
     * param 2의 default는 FALSE
     */
    keypad(sample1, TRUE);
    keypad(sample2, TRUE);
    //keypad(sample3, TRUE);
    //GO:1 sample3를 keypad를 안켠다면?
    //RESULT:1 keypad를 true로 안켜면 F3과 같은 Function key를 읽긴 읽는데, ketpad를 true로 한 window와 다른 값을 읽는다.

    //한개씩 받아보자. 받은뒤 출력하기
    ch = wgetch(sample1);
    mvwprintw(sample1, 1, 1, "Sample1 : %d", ch);
    wrefresh(sample1);

    ch = wgetch(sample2);
    mvwprintw(sample1, s1_sizey / 2, 1, "Sample1-2 : %d", ch); //GO:2 sample2 window에서 받은 값을 sample1에 출력하려고 하면 되나?
    mvwprintw(sample2, s2_sizey / 2, 1, "Sample2 : %d", ch);   //RESULT:2 가능. 문제없이 sample2 wgetch에서 받은 ch 출력, 그렇다면 wgetch는 왜 windows를 argument로 받는지?, RESULT:2 echo mode 시에 해당 window에 값을 반환한다. 이 용도인듯
    wrefresh(sample1);
    wrefresh(sample2);

    ch = wgetch(sample3);
    mvwprintw(sample3, s3_sizey / 2, 1, "Sample3 : %d", ch);
    wrefresh(sample3);

    sleep(3);
    getch(); //이걸 호출하니까 window가 내려가버림. 꺼지는게 아님 커서가 이동된 모양인데..
    //GO:4 window가 내려가버리는건 curse위치를 조정해야하는 것 같은데, 진도를 더 나가봐야할듯

    /* -----------------------------------------------------------------------------------------------------------------------*/
    delwin(sample1);
    delwin(sample2);
    delwin(sample3);
    /**
     * RESULT:0 복수의 wgetch가 있어도, 읽는데는 문제가 없다.
     * document서 getch, wgetch, mvgetch mvwgetch를 사용하는데 nocbreak 모드와 echo mode는 동시에 같이 사용하지 말 것
     * wgetch의 param이 win인 이유는 echo mode시에 값을 어느 윈도우에 echo할지를 결정하기 위함, noecho라면 보이지 않아 체감은 없다.
     */

    endwin();
    return 0;
}

#endif