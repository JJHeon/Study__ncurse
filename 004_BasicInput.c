#include "000_ControlCase.h"

#if _004_BASICINPUT

#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include <ncurses.h>

int main(void)
{
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    char mesg[] = "Enter a string: ";
    char str[80];
    int row, col;

    getmaxyx(stdscr, row, col);
    mvprintw(row / 2, (col - strlen(mesg)) / 2, "%s", mesg); //center of the screen 출력

    getstr(str);                                    //refresh()를 먼저 하고 입력을 대기함, Enter를 쳐야 넘어감
    mvprintw(LINES - 2, 0, "You Entered: %s", str); //LINES는 최대 줄 수
    getch();                                        //refresh()를 먼저 하고 입력을 대기함

    //RESULT: cbreak()가 없으면, new line, EOF 문자가 들어왔을때만 입력을 읽는다. (str 경우)
    //noecho()는 누른 키가 화면에 나타나지않음
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif