#include <curses.h>
#include <string.h>
int main(int argc, char**argv)
{

    initscr();
    noecho();
    raw();

    keypad(stdscr,TRUE);
    int col, row;
    char msg[] = "This is Hell";
    getmaxyx(stdscr,row, col);
    // mvprintw(0,0,"The Width of Screen %d The Height of Screen %d\n",col,row);
    for(int x =0; x<col; x++)
    {
        mvprintw(0, x, "-");
        mvprintw(row-1, x, "-");

    }
    for(int y=0; y< row; y++)
    {    
        mvprintw(y,0,"|");
        mvprintw(y,col-1, "|");
    }
    mvprintw(row/2,(col-strlen(msg))/2,"%s",msg);

    refresh();
    getch();
    endwin();
    return 0;
}