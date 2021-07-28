#include "000_ControlCase.h"

#if _005_BASICATTRIBUTES

#include <stdio.h>

#include <unistd.h>

#include <ncurses.h>

int main(void)
{
    initscr();
    /* -----------------------------------------------------------------------------------------------------------------------*/
    int ch, prev;
    int goto_prev = FALSE, y, x;
    const char *string = "Boris Johnson has spent decades agitating against the European Union and the last five years battling to free the United Kingdom from the shackles of regulation from Brussels. /* RIGHT */ Now he's in the awkward position of finding himself at the mercy of EU leaders for permission to rejoin an international treaty, or risk devastating Britain's multi-billion-dollar legal services industry.";
    int lineend = 0;

    while ((ch = (char)string[lineend++]) != '\0')
    {
        if (prev == '/' && ch == '*')
        {
            attron(A_BOLD);
            goto_prev = TRUE;
        }
        if (goto_prev == TRUE)
        {
            getyx(stdscr, y, x);
            move(y, x - 1);
            printw("%c%c", '/', ch);

            ch = 'a';

            goto_prev = FALSE;
        }
        else
            printw("%c", ch);

        refresh();
        if (prev == '*' && ch == '/')
            attroff(A_BOLD);

        prev = ch;
    }

    getch();

    /* -----------------------------------------------------------------------------------------------------------------------*/
    endwin();
    return 0;
}

#endif