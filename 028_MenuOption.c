/** MenuOption 예제, 
 * 
 */
#include "000_ControlCase.h"

#if _028_MENUOPTION

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Choice 5",
    "Choice 6",
    "Choice 7",
    "Exit",
};

int main(void) {
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices, i;
    ITEM *cur_item;

    /* Initialize curses */
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    //색상 페어링
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

    /* Initialize items */
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for (i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], choices[i]);
    my_items[n_choices] = (ITEM *)NULL;

    //item_opts_off() 표현 속성 off
    item_opts_off(my_items[3], O_SELECTABLE);  //선택불가
    item_opts_off(my_items[6], O_SELECTABLE);

    /* Create menu */
    my_menu = new_menu((ITEM **)my_items);

    /* Set fore ground and back ground of the menu */
    // set_menu_fore() 선택된 아이템 속성 변경
    // set_menu_back() 선택되지 않은 아이템 속성 변경
    set_menu_fore(my_menu, COLOR_PAIR(1) | A_REVERSE);  //반전, 레드 색상
    set_menu_back(my_menu, COLOR_PAIR(2));              //그렇지 않으면 그린 색상

    //set_menu_grey() 메뉴에서 선택 불가능한 아이템 표현 속성 설정
    set_menu_grey(my_menu, COLOR_PAIR(3));  //my_itmes[3], [6] 은 마젠타 색 설정

    /* Post the menu */
    mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
    mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage (F1 to Exit)");
    post_menu(my_menu);
    refresh();

    while ((c = getch()) != KEY_F(1)) {
        switch (c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: /* Enter */
                move(20, 0);
                clrtoeol();
                mvprintw(20, 0, "Item selected is : %s",
                         item_name(current_item(my_menu)));  //현재 선택되있는 메뉴 반환
                pos_menu_cursor(my_menu);                    //커서 위치를 메뉴에서 선택된 아이템 위치에 저장
                break;
        }
    }
    unpost_menu(my_menu);
    for (i = 0; i < n_choices; ++i)
        free_item(my_items[i]);
    free_menu(my_menu);

    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif