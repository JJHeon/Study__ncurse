/** hide_panel(), show_panel() 사용법 예제
 * 함수 및 로직은 022번과 같음
 */
#include "000_ControlCase.h"

#if _023_PANELHIDE

#include <ncurses.h>
#include <panel.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct _PANEL_DATA {
    int hide; /* TRUE if panel is hidden */
} PANEL_DATA;

#define NLINES 10
#define NCOLS 40

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int main(void) {
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    WINDOW *my_wins[3];
    PANEL *my_panels[3];
    PANEL_DATA panel_datas[3];
    PANEL_DATA *temp;
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

    /* Initialize panel datas saying that nothing is hidden */
    panel_datas[0].hide = FALSE;
    panel_datas[1].hide = FALSE;
    panel_datas[2].hide = FALSE;

    /** set_pannel_userptr(pan, ptr) 서 ptr은 const void*로 정해진 형식이 아님을 확인, 022번과 차이가 있음
     * 
     */
    set_panel_userptr(my_panels[0], &panel_datas[0]);
    set_panel_userptr(my_panels[1], &panel_datas[1]);
    set_panel_userptr(my_panels[2], &panel_datas[2]);

    /* Update the stacking order. 2nd panel will be on top */
    update_panels();

    /* Show it on the screen */
    attron(COLOR_PAIR(4));
    mvprintw(LINES - 3, 0, "Show or Hide a window with 'a'(first window)  'b'(Second Window)  'c'(Third Window)");
    mvprintw(LINES - 2, 0, "F1 to Exit");

    attroff(COLOR_PAIR(4));
    doupdate();

    /** RESULT:
     *  show_panel 단계에서 stack 최상위로 놓음 & 보이게 바꾸면서
     */
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case 'a':
                temp = (PANEL_DATA *)panel_userptr(my_panels[0]);
                if (temp->hide == FALSE) {
                    hide_panel(my_panels[0]);
                    temp->hide = TRUE;
                } else {
                    show_panel(my_panels[0]);
                    temp->hide = FALSE;
                }
                break;
            case 'b':
                temp = (PANEL_DATA *)panel_userptr(my_panels[1]);
                if (temp->hide == FALSE) {
                    hide_panel(my_panels[1]);
                    temp->hide = TRUE;
                } else {
                    show_panel(my_panels[1]);
                    temp->hide = FALSE;
                }
                break;
            case 'c':
                temp = (PANEL_DATA *)panel_userptr(my_panels[2]);
                if (temp->hide == FALSE) {
                    hide_panel(my_panels[2]);
                    temp->hide = TRUE;
                } else {
                    show_panel(my_panels[2]);
                    temp->hide = FALSE;
                }
                break;
        }
        update_panels();
        doupdate();
    }

    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

/* Put all the windows */
void init_wins(WINDOW **wins, int n) {
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
void win_show(WINDOW *win, char *label, int label_color) {
    int startx, starty, height, width;

    getbegyx(win, starty, startx);
    getmaxyx(win, height, width);

    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, width - 2);
    mvwaddch(win, 2, width - 1, ACS_RTEE);

    print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color) {
    int length, x, y;
    float temp;

    if (win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if (startx != 0)
        x = startx;
    if (starty != 0)
        y = starty;
    if (width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length) / 2;
    x = startx + (int)temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}

#endif
