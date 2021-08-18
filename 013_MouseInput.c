#include "000_ControlCase.h"

#if _013_MOUSEINPUT

#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Exit"};

int n_choices = sizeof(choices) / sizeof(char *);

int startx = 0;
int starty = 0;

void print_menu(WINDOW *menu_win, int highlight);
void report_choice(int mouse_x, int mouse_y, int *p_choice);

int main(void)
{
    initscr();
    /**
     * RESULT: 예제인데 Window terminal로 구동된 WSL Ubuntu가 mouse를 인식하지 않는 것인지, wgetch(menu_win)에서 KEY_MOUSE값을 반환하지 않고 LINE Number같은? 값을 반환한다.
     * 공식 문서에는 그러한 예외사항이 적혀져 있지 않은걸 보면, 가상머신 상의 리눅스라 그런걸 수 도 있는 것 같은데, 명확하게는 모르겠다.
     * 문제점을 알기위해 여러가지 PRINT해봤는데 일단 MOUSE 사용이 안됨
     * 
     */
    /* -----------------------------------------------------------------------------------------------------------------------*/
    int c, choice = 0;
    WINDOW *menu_win;
    MEVENT event;

    clear();
    noecho();
    cbreak();

    /* Try to put the window in the middle of screen */
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

    attron(A_REVERSE);
    mvprintw(23, 1, "Click on Exit to quit (Works best in a virtual console) %d ", KEY_MOUSE);

    refresh();
    attroff(A_REVERSE);

    /* Print the menu for the first time */
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    print_menu(menu_win, 1);

    /* Get all the mouse events */
    int rm = mousemask(ALL_MOUSE_EVENTS, NULL);
    mvprintw(25, 1, "mousemask return value : %d, ALL_MOUSE_EVENTS : %d", rm, ALL_MOUSE_EVENTS);
    mvprintw(26, 1, "KEYMOUSE : %d", KEY_MOUSE);
    refresh();

    while (1)
    {
        c = wgetch(menu_win);
        mvprintw(24, 1, "wgetch value : %4d", c);
        refresh();
        switch (c)
        {
        case KEY_MOUSE:
            if (getmouse(&event) == OK)
            {

                /* When the user clicks left mouse button */
                if (event.bstate & BUTTON1_PRESSED)
                {
                    report_choice(event.x + 1, event.y + 1, &choice);
                    if (choice == -1) //Exit chosen
                        goto end;
                    mvprintw(22, 1, "Choice made is : %d String Chosen is \"%10s\"", choice, choices[choice - 1]);
                    refresh();
                }
            }
            else
            {
                mvprintw(24, 1, "Fail");
                refresh();
            }
            print_menu(menu_win, choice);
            break;

        default:
            break;
        }
    }
end:
    /* -----------------------------------------------------------------------------------------------------------------------*/
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
        if (highlight == i + 1)
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
void report_choice(int mouse_x, int mouse_y, int *p_choice)
{
    int i, j, choice;

    i = startx + 2;
    j = starty + 3;

    for (choice = 0; choice < n_choices; ++choice)
        if (mouse_y == j + choice && mouse_x >= i && mouse_x <= i + strlen(choices[choice]))
        {
            if (choice == n_choices - 1)
                *p_choice = -1;
            else
                *p_choice = choice + 1;
            break;
        }
}

#endif