/** Form 사용법 기본 예제
 * 여기서의 Form은 입력을 받고 다양한 종류의 일을 하는 것, 입력칸을 의미
 *
 * 
 */
#include "000_ControlCase.h"

#if _029_FORMBASIC

#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ncurses.h>
#include <form.h>

int main(void) {
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/

    FIELD* field[3];
    FORM* my_form;
    int ch;

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /** new_field(높이, 넓이, starty, startx, offscreen 줄 수 , 추가 작업용 버퍼수),
     * offscreen은 필드의 어느 정도를 보여줄 것인지 결정하는 값
     * 0 이면, 필드의 일부가 표시되지 않아서 스크롤이 필요한 경우가 아니면 항상 전체 필드를 보여줌
     * 폼 라이브러리는 사용자가 입력하는 데이터를 저장하기 위해서 필드당 버퍼를 하나씩 할당
     */
    field[0] = new_field(1, 10, 4, 19, 0, 0);
    field[1] = new_field(1, 10, 6, 19, 0, 0);
    field[2] = NULL;

    set_field_back(field[0], A_UNDERLINE);
    field_opts_off(field[0], O_AUTOSKIP); //필드가 모두 채워졌을 경우, 다른 필드 자동으로 이동 금지

    set_field_back(field[1], A_UNDERLINE);
    field_opts_off(field[1], O_AUTOSKIP);

    my_form = new_form(field);
    post_form(my_form);
    refresh();

    mvprintw(4, 10, "Value 1: ");
    mvprintw(6, 10, "Value 2: ");
    refresh();

    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case KEY_DOWN:
                form_driver(my_form, REQ_NEXT_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            case KEY_UP:
                form_driver(my_form, REQ_PREV_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            default:
                form_driver(my_form, ch);
                break;
        }
    }

    unpost_form(my_form);
    free_form(my_form);
    free_field(field[0]);
    free_field(field[1]);

    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif