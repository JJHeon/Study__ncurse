#include "000_ControlCase.h"

#if _010_BASICCOLORS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

#include <ncurses.h>

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);

int main(void)
{
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/

    //has_colors가 terminal의 색상 기능 지원 여부 확인
    if (has_colors() == FALSE)
    {
        endwin();
        printf("You terminal does not support color\n");
        exit(1);
    }

    //
    /** start_colors
     * Color 사용을 위해 필요, 터미널에서 지원되는 모든 색을 초기화해서 준비 
     * 미리 정의된 상수를 통해 사용 가능
     * 실제로 사용하기 위해선 색상짝을 정의 해야하는데,
     * 색은 항상 색상짝의 꼴로 쓰여진다.
     * init_pair()를 통해 글자색과 글자배경색을 정의해야만 쓸 수 있음
     * 그 다음 COLOR_PAIR(1) 함수와 함께 일반 속성처럼 쓰여짐
     */
    start_color(); //Start color
    init_pair(1, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
    attroff(COLOR_PAIR(1));

    /* -----------------------------------------------------------------------------------------------------------------------*/
    //GO: param 3은 배경색인지 확인
    init_pair(2, COLOR_MAGENTA, COLOR_GREEN);
    attron(COLOR_PAIR(2));
    print_in_middle(stdscr, LINES / 2 + 1, 0, 0, "MAGENTA!! GREEN!");
    attroff(COLOR_PAIR(2));
    //RESULT: 예상대로 init_pair의 2번째 parameter 글자 배경색.

    /** 사용할 수 있는 목록
     *  COLOR_BLACK   0                                                      
        COLOR_RED     1                                                      
        COLOR_GREEN   2                                                      
        COLOR_YELLOW  3                                                      
        COLOR_BLUE    4                                                      
        COLOR_MAGENTA 5                                                      
        COLOR_CYAN    6                                                      
        COLOR_WHITE   7     
     */

    /* -----------------------------------------------------------------------------------------------------------------------*/
    //GO: 색상 정의 바꾸기
    init_color(COLOR_RED, 400, 0, 0);
    /** init_color param
     * param 1 : color name
     * param 2, 3, 4,: rbg content min =0, max = 1000, r,g,b
     * 만약 터미널이 색상 정의를 변경하지 못한다면 ERR RETURN
     * can_change_color() 함수는 터미널이 색상을 바꿀 수 잇는 기능이 있는지 없는지 확인
     */
    init_pair(3, COLOR_RED, COLOR_WHITE);
    attron(COLOR_PAIR(3));
    print_in_middle(stdscr, LINES / 2 + 2, 0, 0, "Is its color changed?");
    attroff(COLOR_PAIR(3));
    //RESULT: 빨강색이 옅어지는 것 확인

    /* -----------------------------------------------------------------------------------------------------------------------*/
    getch();

    endwin();
    return 0;
}
/**
 * 이 함수는 그저 중심 위치에 글자출력만을 담당
 */
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{
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
    mvwprintw(win, y, x, "%s", string);
    refresh();
}

#endif