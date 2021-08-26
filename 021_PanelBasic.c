/** Panel 기본 사용법 예제, 3개의 겹치는 패널을 만들고 화면을 보여주는 예제
 *  링크 옵션 -lpanel, <panel.h> 필요
 */
#include "000_ControlCase.h"

#if _021_PANELBASIC

#include <ncurses.h>
#include <panel.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    WINDOW* my_wins[3];
    PANEL* my_panels[3];
    int lines = 10, cols = 40, y = 2, x = 4, i;

    cbreak();
    noecho();
    refresh();
    /* Create windows for the panels */
    my_wins[0] = newwin(lines, cols, y, x);
    my_wins[1] = newwin(lines, cols, y + 1, x + 5);
    my_wins[2] = newwin(lines, cols, y + 2, x + 10);

    /**
     * Create borders around the windows so that you can see the effect of panels
     */
    for (i = 0; i < 3; ++i) {
        box(my_wins[i], 0, 0);
        // wrefresh(my_wins[i]);
        // sleep(1);
    }

    /* Attach a panel to each window. Order is bottom up */
    my_panels[0] = new_panel(my_wins[0]);  //Push 0, order : stdscr-0
    my_panels[1] = new_panel(my_wins[1]);  //Push 1, order : stdscr-0-1
    my_panels[2] = new_panel(my_wins[2]);  //Push 2, order : stdscr-0-1-2

    /* Update the stacking order. 2nd panel will be on top */
    update_panels();  //virtual screen에 stack 관계 반영

    /* Show it on the screen */
    doupdate();  //virtual screen -> physical screen 반영, 흔히 하는 wrefesh 는 wnoutrefresh + doupdate 조합이다.
    /**
     * wnoutrefresh는 window를 virtual screen으로 copy.
     * 다수 window가 존재할 경우 wrefresh를 남발하면 screen이 자주 깜빡임 (CPU가 더 많이 일함)
     * wrefresh 한번에 wnoutrefresh + doupdate가 한번씩 실행되는데, 이 때문에 자주 깜빡임
     * doupdate는 다수의 window가 virtual screen으로 옮겨진 후, 단 한번만 호출해도 된다.
     * 때문에 pannel을 사용할 떈, doudpate를 분리해서 따로 사용함 
     */

    getch();
    /** RESULT:
     * 이 예제는 단순히 panel을 이용해 3개 window를 쌓는 것 뿐.
     */
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif