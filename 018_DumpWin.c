/** putwin(), getwin(), copywin()에 대해
 * 
 */
#include "000_ControlCase.h"

#if _018_DUMPWIN

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

bool fill_box_window(WINDOW* win, int boundary_y, int boundary_x, const char* string);

int main(void) {
    initscr();

    refresh();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    int scr_max_y = 0, scr_max_x = 0;
    int ch = 0;
    const char* str1 = "Taliban spokesperson Zabiullah Mujahid said at a news conference on Tuesday that women should not go to work for their own safety, undermining the groups efforts to convince international observers that the group would be more tolerant towards women than when they were last in power. The instruction came the same day that the World Bank halted funding in Afghanistan, citing concerns about the safety of women, and within hours of the UN calling for a transparent and prompt investigation into reports of human rights abuses since the Taliban takeover. Mujahid said the guidance to stay at home would be temporary, and would allow the group to find ways to ensure that women are not treated in a disrespectful way or God forbid, hurt. He admitted the measure was necessary because the Talibans soldiers keep changing and are not trained.";
    const char* str2 = "Hello This is the First.";
    const char* str3 = "Hello This is the Second.";

    getmaxyx(stdscr, scr_max_y, scr_max_x);

    WINDOW* window1 = newwin(10, scr_max_x, 3, 0);
    WINDOW* window2 = newwin(5, scr_max_x, 13, 0);

    mvprintw(0, 0, "Size of Screen | Y : %3d, X : %3d", scr_max_y, scr_max_x);
    box(window1, 0, 0);
    box(window2, 0, 0);
    wrefresh(window1);
    wrefresh(window2);
    refresh();

    /*
    gets_s(strbuf, sizeof(strbuf)); //gcc에서 현재 허용하지 않음 (구현되있지 않음)
    fgets(strbuf, sizeof(strbuf), stdin); //사용가능, noecho모드가 아닌데도 보이지않음, 입력은 되는듯함, terminal 제어를 가로채다보니 입력글자가 보이지않는듯
    mvprintw(2, 0, "Type : %s", strbuf);
    refresh();
    */

    fill_box_window(window1, 1, 1, str1);
    fill_box_window(window2, 1, 1, str2);

    //GO: putwin, getwin test
    FILE* file1 = fopen("windowdump1.txt", "w");
    putwin(window1, file1);
    wrefresh(window1);
    sleep(2);

    FILE* file2 = fopen("windowdump2.txt", "rw");
    putwin(window2, file2);  //window2, file2에 str2내용 "Hello This is the First.";
    wrefresh(window2);
    sleep(2);

    werase(window2);  //window내용 모두를 지움
    wrefresh(window2);
    sleep(2);

    box(window2, 0, 0);
    fill_box_window(window2, 1, 1, str3);  //새로그린 window2에 str3내용 "Hello This is the Second."
    wrefresh(window2);
    sleep(2);

    //werase(window2);
    werase(window2);
    wrefresh(window2);
    sleep(2);

    /** RESULT:
     * putwin을 사용하려면 FILE 포인터를 w로 open
     * getwin을 사용하려면 FILE 포인터를 r로 open
     */
    window2 = getwin(file2);  //불러온 그대로 잘 출력됨
    wrefresh(window2);
    sleep(2);
    // FILE* file2 = fopen("windowdump2.txt", "r");
    // getwin(file2);
    // sleep(2);

    getch();
    fclose(file1);
    fclose(file2);
    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

bool fill_box_window(WINDOW* win, int boundary_y, int boundary_x, const char* string) {
    int size_y = 0, size_x = 0;
    int i = 0;
    int y = boundary_y;
    int x = boundary_x;

    getmaxyx(win, size_y, size_x);

    while (string[i] != '\0') {
        if (x > (size_x - 1 - boundary_x)) {
            x = boundary_x;
            y++;
            continue;
        } else if (y > (size_y - 1 - boundary_y)) {
            break;
        }

        mvwaddch(win, y, x++, string[i++]);
        wrefresh(win);
    }

    return true;
}

#endif