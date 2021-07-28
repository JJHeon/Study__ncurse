#include "000_ControlCase.h"

#if _008_WINDOW

#include <stdio.h>

#include <unistd.h>

#include <ncurses.h>

WINDOW *create_newwin(int height, int width, int start_line, int start_col)
{
    WINDOW *local_win;

    local_win = newwin(height, width, start_line, start_col);
    box(local_win, 0, 0);
    /** 0, 0 default characters
     * for the vertical and horizontal lines ???
     */

    wrefresh(local_win);

    return local_win;
}

void destroy_win(WINDOW *local_win)
{
    /** box(local_win, ' ', ' ');
     * 이건 원래 있던 것을 지우지 못할 거라고 원문에서는 말하고 있음. corners를 남기게 된다는데?
    */
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    /* The parameters taken are                                                     
         * 1. win: the window on which to operate                                       
         * 2. ls: character to be used for the left side of the window                  
         * 3. rs: character to be used for the right side of the window                 
         * 4. ts: character to be used for the top side of the window                   
         * 5. bs: character to be used for the bottom side of the window                
         * 6. tl: character to be used for the top left corner of the window            
         * 7. tr: character to be used for the top right corner of the window           
         * 8. bl: character to be used for the bottom left corner of the window         
         * 9. br: character to be used for the bottom right corner of the window        
         */
    wrefresh(local_win);
    delwin(local_win); //window 를 지움
}

int main(void)
{
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    WINDOW *win;
    int start_line, start_col, line = 3, col = 10;
    int ch;
    start_line = (LINES - line) / 2; // center 계산
    start_col = (COLS - col) / 2;

    //wborder test
    win = newwin(line, col, start_line, start_col);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
    delwin(win);
    win = NULL;
    sleep(5);

    /**
     * cbreak는 input buffering off를 수행, 입력된 값이 바로 나에게 옴
     * 그러면서 ctrl + c 와 같은 디바이스 특수 입력에 대해 매크로로 맵핑함
     */
    cbreak();
    curs_set(FALSE); //curse를 보이지 않게

    keypad(stdscr, TRUE);

    printw("Press F1 to exit");
    refresh();

    win = create_newwin(line, col, start_line, start_col);

    while ((ch = getch()) != KEY_F(1))
    {
        switch (ch)
        {
        case KEY_LEFT:
            destroy_win(win);
            win = create_newwin(line, col, start_line, --start_col);
            break;
        case KEY_RIGHT:
            destroy_win(win);
            win = create_newwin(line, col, start_line, ++start_col);
            break;
        case KEY_UP:
            destroy_win(win);
            win = create_newwin(line, col, --start_line, start_col);
            break;
        case KEY_DOWN:
            destroy_win(win);
            win = create_newwin(line, col, ++start_line, start_col);
            break;

        default:
            break;
        }
    }
    /* ----------------------------------------------------------------------------------------------------------------------- */
    /** RESULT: 박스가 움직이는데, 터미널크기가 변경되도 그 위치 그대로 있다
     * 화면 Boundery로 나가게 되면 안보이고 다시 돌아오면 보인다
     * Boundery 밖으로 나가더라도 터미널 크기를 키우면 보인다
     */
    endwin();
    return 0;
}

#endif