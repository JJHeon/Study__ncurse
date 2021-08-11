#include "000_ControlCase.h"

#if _011_KEYEXAMPLE

#include <stdio.h>

#include <unistd.h>

#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Exit"};

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main(void)
{
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    clear();
    noecho();
    cbreak();
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Please enter to select a choice, This is not the paste text");
    refresh();
    print_menu(menu_win, highlight);

    while (1)
    {
        c = wgetch(menu_win);
        switch (c)
        {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_choices)
                highlight = 1;
            else
                ++highlight;
            break;
        case 10:
            choice = highlight;
            break;

        default:
            mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
            refresh();
            break;
        }

        print_menu(menu_win, highlight);
        if (choice != 0)
            break;
    }

    //%n도 출력 가능 확인
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);

    //이 함수는 커서 오른쪽의 현재 라인을 지운다. 끝까지.
    clrtoeol();
    refresh();

    /* -----------------------------------------------------------------------------------------------------------------------*/
    /** RESULT: menu_win을 통해 현재 wgetch를 통해서 window 를 통해 character를 read하고 있는데, 여러 window가 존재하면 어떻게 할것인가?, 
     * 어느쪽으로 읽는 것인지 명확하게 할 필요가 있다.
     * 
     */
    endwin();
    return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i)
    {
        if (highlight == i + 1) /* Hight light the present choice */
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }

    wrefresh(menu_win);
}

#endif