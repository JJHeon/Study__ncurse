/** Panel 기본 사용법 예제 2, Panel을 이용한 탭키로 전환될 수 있는 3개의 윈도우
 *  링크 옵션 -lpanel, <panel.h> 필요
 */
#include "000_ControlCase.h"

#if _022_PANELBASIC2

#include <ncurses.h>
#include <panel.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NLINES 10
#define NCOLS 40

void init_wins(WINDOW** wins, int n);
void win_show(WINDOW* win, char* label, int label_color);
void print_in_middle(WINDOW* win, int starty, int startx, int width, char* staring, chtype color);

int main(void) {
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/

    WINDOW* my_wins[3];
    PANEL* my_panels[3];
    PANEL* top;

    int ch;
    /* Initialize curses */
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /* Initialize all the colors */
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    init_wins(my_wins, 3);

    /* Attach a panel to each window */
    my_panels[0] = new_panel(my_wins[0]);
    my_panels[1] = new_panel(my_wins[1]);
    my_panels[2] = new_panel(my_wins[2]);

    /* Set up the user pointers to the next panel */
    /**
     * 패널의 유저 포인터를 지정, set_panel_userptr(pan,ptr), 
     * 
     * panel_userptr(pan) 은 인자인 pan 을 주면 주어진 pan에대한 userptr은 반환하는데 set_panel_userptr에서 설정한 값임
     * 
     * 예로 최초 top = my_panels[2] 였다면, 최초 panel_userptr에서 top은 my_panels[2]이고, 이에 해당하는 ptr은 my_panels[0] 반환하고 이를 Top으로 올림
     * (PANEL*)panel_userptr(top); 다음과 같은 형태에서 반환된 userptr은 (PANEL*)로 형변환되서 사용될 수 있음
     * top_panel(pan)은 인자로 pan이 필요
     */
    set_panel_userptr(my_panels[0], my_panels[1]);
    set_panel_userptr(my_panels[1], my_panels[2]);
    set_panel_userptr(my_panels[2], my_panels[0]);

    /* Update the stacking order. 2nd panel will be on top */
    update_panels();

    /* Show it on the screen */
    attron(COLOR_PAIR(4));
    mvprintw(LINES - 2, 0, "Use tab to browse through the windows (F1 to Exit)");
    attroff(COLOR_PAIR(4));
    doupdate();

    top = my_panels[2];
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case 9:  //tab
                top = (PANEL*)panel_userptr(top);
                top_panel(top);  //인지로 주어진 패널을 패널스택 최상위로 옮김
                break;

            default:
                break;
        }

        update_panels();  //window에서 wnoutrefresh와 같은 역할
        doupdate();
    }

    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

/* Put all the windows */
void init_wins(WINDOW** wins, int n) {
    int x, y, i;
    char label[80];

    y = 2;
    x = 10;
    for (i = 0; i < n; ++i) {
        wins[i] = newwin(NLINES, NCOLS, y, x);
        sprintf(label, "Window Number %d", i + 1);
        win_show(wins[i], label, i + 1);
        y += 3;
        x += 7;
    }
}

/* Show the window with a border and a label */
void win_show(WINDOW* win, char* label, int label_color) {
    int startx, starty, height, width;

    getbegyx(win, starty, startx);
    getmaxyx(win, height, width);

    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, width - 2);
    mvwaddch(win, 2, width - 1, ACS_RTEE);

    print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW* win, int starty, int startx, int width, char* string, chtype color) {
    int length, x, y;
    float temp;
    if (win == NULL) win = stdscr;
    getyx(win, y, x);

    if (startx != 0) x = startx;
    if (starty != 0) y = starty;
    if (width == 0) width = 80;

    length = strlen(string);
    temp = (width - length) / 2;
    x = startx + (int)temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}

#endif