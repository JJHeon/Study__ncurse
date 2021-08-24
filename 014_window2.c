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
    int screen_num;
    WIN *selected_screen;
} MOTION;

WIN *create_newwin(int height, int width, int start_line, int start_col);
WIN *delete_win(WIN *p_WIN);

void draw_box(WIN *p_WIN);
void init_motion(MOTION *p_motion);

bool check_in_user_curser(WIN *p_WIN, int curser_y, int curser_x);

WIN *screen[2];

int main(void) {
    initscr();
    /**
     * 박스를 움직이는 커서 $
     * window를 create 및 delate 하면서 이동
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
    refresh();

    /** 21.08.19 문제있음, 네모박스가 안보임 
     *  네모를 출력하고 while 을 넘어간 순간 화면전환을 해버리는데, 화면전환을 누가하는지?
     *  21.08.23 while 전 refresh()가 화면을 바꿔버림. -> 015으로 해결
     *  21.08.23 다른 문제 발생, stdscr에 출력하는 curser $가 기존 출력되있던 screen 0번과 1번의 박스를 지움.
     *  결론적으로 srdscr과 window들은 출력을 공유하기 때문에 발생하는 문제로 보임
     *  21.08.24 박스지움 문제 해결
     *  21.08.24 KEY_ENTER가 먹지않는 새로운 문제 발생, 016 참조
     *  016참조, KEY_ENTER 기능불가, ASCII 10이 대체
     *  큰 박스를 움직이는데 문제 발생 (segmentation fault), 작은 박스를 움직이는데 문제없음 ->빈 Memory 참조 문제, 해결
     *  
     */

    init_motion(&user_move);
    screen[0] = create_newwin(screen1_sizey, screen1_sizex, screen1_starty, screen1_startx);
    screen[1] = create_newwin(screen2_sizey, screen2_sizex, screen2_starty, screen2_startx);
    max_x = getmaxx(stdscr);
    max_y = getmaxy(stdscr);

    while ((ch = getch()) != KEY_F(1)) {
        mvprintw(47, 0, "CH : %4u", ch);
        refresh();
        switch (ch) {
            case KEY_LEFT:
                if (user_move.user_curser_x > 0) {
                    mvprintw(user_move.user_curser_y, user_move.user_curser_x--, " ");

                    if (user_move.selected_screen) {
                        WIN temp = *(user_move.selected_screen);

                        delete_win(user_move.selected_screen);
                        user_move.selected_screen = create_newwin(temp.height, temp.width, temp.starty, --temp.startx);
                        screen[user_move.screen_num] = user_move.selected_screen;
                    }
                }

                break;
            case KEY_RIGHT:
                if (user_move.user_curser_x < max_x) {
                    mvprintw(user_move.user_curser_y, user_move.user_curser_x++, " ");

                    if (user_move.selected_screen) {
                        WIN temp = *(user_move.selected_screen);

                        delete_win(user_move.selected_screen);
                        user_move.selected_screen = create_newwin(temp.height, temp.width, temp.starty, ++temp.startx);
                        screen[user_move.screen_num] = user_move.selected_screen;
                    }
                }
                break;
            case KEY_UP:
                if (user_move.user_curser_y > 0) {
                    mvprintw(user_move.user_curser_y--, user_move.user_curser_x, " ");

                    if (user_move.selected_screen) {
                        WIN temp = *(user_move.selected_screen);

                        delete_win(user_move.selected_screen);
                        user_move.selected_screen = create_newwin(temp.height, temp.width, --temp.starty, temp.startx);
                        screen[user_move.screen_num] = user_move.selected_screen;
                    }
                }
                break;
            case KEY_DOWN:
                if (user_move.user_curser_y < max_y) {
                    mvprintw(user_move.user_curser_y++, user_move.user_curser_x, " ");

                    if (user_move.selected_screen) {
                        WIN temp = *(user_move.selected_screen);

                        delete_win(user_move.selected_screen);
                        user_move.selected_screen = create_newwin(temp.height, temp.width, ++temp.starty, temp.startx);
                        screen[user_move.screen_num] = user_move.selected_screen;
                    }
                }
                break;
            case KEY_ENTER:  //현재 개발PC서 KEY_ENTER는 사용불가
            case 10:         //Enter == 10
                // mvprintw(30, 0, "ENter!");  //for debug, OK
                // refresh();
                if (!user_move.selected_screen) {
                    // mvprintw(31, 0, "Yes!");  //for debug, OK
                    // refresh();
                    for (int i = 0; i < CURRENT_SCREEN_NUM; i++) {
                        //for (int i = 0; i < 1; i++) {
                        if (check_in_user_curser(screen[i], user_move.user_curser_y, user_move.user_curser_x)) {
                            user_move.selected_screen = screen[i];
                            user_move.screen_num = i;

                            break;
                        }
                    }
                } else {
                    // mvprintw(32, 0, "Fail"); //for debug, OK
                    // refresh();
                    user_move.selected_screen = NULL;
                }

                break;
            default:
                break;
        }

        for (int i = 0; i < CURRENT_SCREEN_NUM; i++) draw_box(screen[i]);
        mvprintw(user_move.user_curser_y, user_move.user_curser_x, "$");
        mvprintw(0, 0, "MAX Y : %3d, MAX X : %3d | User curser Y : %3d, X : %3d || KEY VALUE : %u", max_y, max_x, user_move.user_curser_y, user_move.user_curser_x, ch);
        getyx(stdscr, real_y, real_x);
        mvprintw(1, 0, "Get Y : %3d, Get X : %3d", real_y, real_x);

        refresh();
    }

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
    p_motion->screen_num = -1;
}

WIN *create_newwin(int height, int width, int starty, int startx) {
    WIN *local_win = (WIN *)malloc(sizeof(WIN));

    local_win->screen = newwin(height, width, starty, startx);
    local_win->startx = startx;
    local_win->starty = starty;
    local_win->height = height;
    local_win->width = width;

    //box(local_win->screen, 0, 0);
    //wrefresh(local_win->screen);
    draw_box(local_win);

    /** 0, 0 default characters
     * for the vertical and horizontal lines ???
     */

    return local_win;
}

WIN *delete_win(WIN *p_WIN) {
    wborder(p_WIN->screen, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(p_WIN->screen);

    delwin(p_WIN->screen);
    free(p_WIN);
}

void draw_box(WIN *p_WIN) {
    //wborder(p_WIN->screen, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    //wrefresh(p_WIN->screen);
    box(p_WIN->screen, 0, 0);
    wrefresh(p_WIN->screen);
}

bool check_in_user_curser(WIN *p_WIN, int curser_y, int curser_x) {
    // mvprintw(33, 0, "y : %d, x : %d | starty : %d, y-expand : %d | startx : %d, x-expand : %d", curser_y, curser_x, p_WIN->starty, (p_WIN->starty + p_WIN->height - 1), p_WIN->startx, (p_WIN->startx + p_WIN->width - 1)); //for debug, OK
    // refresh();
    if (p_WIN->starty <= curser_y && curser_y <= (p_WIN->starty + p_WIN->height - 1) && p_WIN->startx <= curser_x && curser_x <= (p_WIN->startx + p_WIN->width - 1))
        return true;
    else
        return false;
}

#endif