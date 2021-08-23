#include "000_ControlCase.h"

#if _014_WINDOW2

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CURRENT_SCREEN_NUM 2

typedef struct _WIN_struct {
    int startx, starty;
    int height, width;
    WINDOW *screen;
} WIN;

typedef struct _key_motion {
    int user_curser_x;
    int user_curser_y;
    WIN *selected_screen;
} MOTION;

WIN *create_newwin(int height, int width, int start_line, int start_col);
WIN *delete_win(WIN *p_WIN);

void init_motion(MOTION *p_motion);

bool check_in_user_curser(WIN *p_WIN, int curser_y, int curser_x);

WIN *screen[2];

int main(void) {
    initscr();
    /**
     * 
     */
    /* -----------------------------------------------------------------------------------------------------------------------*/
    int ch = 0;
    int max_x = 0, max_y = 0;

    int screen1_starty = 2;  //2 previous value
    int screen1_startx = 0;  //0 previous value
    int screen1_sizey = 5;
    int screen1_sizex = 5;

    int screen2_starty = 10;  //8 previous value
    int screen2_startx = 3;   //0 previous value
    int screen2_sizey = 3;
    int screen2_sizex = 3;

    int real_y = 0;
    int real_x = 0;

    MOTION user_move;

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /** 21.08.19 문제있음, 네모박스가 안보임 
     *  네모를 출력하고 while 을 넘어간 순간 화면전환을 해버리는데, 화면전환을 누가하는지?
     *  21.08.23 refresh()가 화면을 바꿔버림.
     * / 
    //
    
    init_motion(&user_move);
    screen[0] = create_newwin(screen1_sizey, screen1_sizex, screen1_starty, screen1_startx);
    screen[1] = create_newwin(screen2_sizey, screen2_sizex, screen2_starty, screen2_startx);
    max_x = getmaxx(stdscr);
    max_y = getmaxy(stdscr);

    sleep(1);
    //wgetch(screen[0]->screen);
    //wgetch(stdscr);
    refresh();
    sleep(2);
    // while ((ch = getch()) != KEY_F(1)) {
    //     switch (ch) {
    //         case KEY_LEFT:
    //             if (user_move.user_curser_x > 0) {
    //                 mvprintw(user_move.user_curser_y, user_move.user_curser_x--, " ");

    //                 if (user_move.selected_screen) {
    //                     WIN temp = *(user_move.selected_screen);

    //                     delete_win(user_move.selected_screen);
    //                     user_move.selected_screen = create_newwin(temp.height, temp.width, temp.starty, --temp.startx);
    //                 }
    //             }

    //             break;
    //         case KEY_RIGHT:
    //             if (user_move.user_curser_x < max_x) {
    //                 mvprintw(user_move.user_curser_y, user_move.user_curser_x++, " ");

    //                 if (user_move.selected_screen) {
    //                     WIN temp = *(user_move.selected_screen);

    //                     delete_win(user_move.selected_screen);
    //                     user_move.selected_screen = create_newwin(temp.height, temp.width, temp.starty, ++temp.startx);
    //                 }
    //             }
    //             break;
    //         case KEY_UP:
    //             if (user_move.user_curser_y > 0) {
    //                 mvprintw(user_move.user_curser_y--, user_move.user_curser_x, " ");

    //                 if (user_move.selected_screen) {
    //                     WIN temp = *(user_move.selected_screen);

    //                     delete_win(user_move.selected_screen);
    //                     user_move.selected_screen = create_newwin(temp.height, temp.width, --temp.starty, temp.startx);
    //                 }
    //             }
    //             break;
    //         case KEY_DOWN:
    //             if (user_move.user_curser_y < max_y) {
    //                 mvprintw(user_move.user_curser_y++, user_move.user_curser_x, " ");

    //                 if (user_move.selected_screen) {
    //                     WIN temp = *(user_move.selected_screen);

    //                     delete_win(user_move.selected_screen);
    //                     user_move.selected_screen = create_newwin(temp.height, temp.width, ++temp.starty, temp.startx);
    //                 }
    //             }
    //             break;
    //         case KEY_ENTER:

    //             if (!user_move.selected_screen) {
    //                 for (int i = 0; i < CURRENT_SCREEN_NUM; i++)
    //                     if (check_in_user_curser(&screen[i], user_move.user_curser_y, user_move.user_curser_x)) {
    //                         user_move.selected_screen = &screen[i];
    //                         break;
    //                     }
    //             } else
    //                 user_move.selected_screen = NULL;

    //             break;
    //         default:
    //             break;
    //     }
    //     mvprintw(user_move.user_curser_y, user_move.user_curser_x, "$");
    //     mvprintw(0, 0, "MAX Y : %3d, MAX X : %3d | User curser Y : %3d, X : %3d", max_y, max_x, user_move.user_curser_y, user_move.user_curser_x);
    //     getyx(stdscr, real_y, real_x);
    //     mvprintw(1, 0, "Get Y : %3d, Get X : %3d", real_y, real_x);
    //     refresh();
    // }

    delete_win(screen[0]);
    delete_win(screen[1]);
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

void init_motion(MOTION *p_motion) {
    p_motion->selected_screen = NULL;
    p_motion->user_curser_y = 2;
    p_motion->user_curser_x = 0;
}

WIN *create_newwin(int height, int width, int starty, int startx) {
    WIN *local_win = (WIN *)malloc(sizeof(WIN));

    local_win->screen = newwin(height, width, starty, startx);
    local_win->startx = startx;
    local_win->starty = starty;

    box(local_win->screen, 0, 0);
    /** 0, 0 default characters
     * for the vertical and horizontal lines ???
     */

    wrefresh(local_win->screen);

    return local_win;
}

WIN *delete_win(WIN *p_WIN) {
    wborder(p_WIN->screen, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(p_WIN->screen);

    delwin(p_WIN->screen);
    free(p_WIN);
}

bool check_in_user_curser(WIN *p_WIN, int curser_y, int curser_x) {
    if (p_WIN->starty <= curser_y && curser_y <= (p_WIN->starty + p_WIN->height - 1) && p_WIN->startx <= curser_x && curser_x <= (p_WIN->startx + p_WIN->width - 1))
        return true;
    else
        return false;
}

#endif