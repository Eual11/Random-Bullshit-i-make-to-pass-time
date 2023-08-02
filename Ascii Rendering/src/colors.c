#include <curses.h>


int main(int argc, char argv)
{
    initscr();
    noecho();
    raw();

    start_color();
    init_pair(1,COLOR_RED,COLOR_WHITE);
    init_pair(0, COLOR_WHITE,COLOR_BLACK);

    attron(COLOR_PAIR(0));
    printw("This will be printed in normal color\n");
    attroff(COLOR_PAIR(0));
    attron(COLOR_PAIR(1));
    printw("Perhaps something different \n");
    getch();
    endwin();

    return 0;
}