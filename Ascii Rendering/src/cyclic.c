#include <curses.h>
#include <Windows.h>
#include <sodium.h>
#include <stdlib.h>
const int MAX_ITER = 90000;
#include <math.h>
# define M_PI     3.14159265358979323846

typedef struct vert
{
    int x;
    int y;
} vert;
void fractal_generate(WINDOW* win, unsigned int size);
int main(void)
{
    printf("PRESS ENTER FOR FULL SCREEN MODE\n");
    getchar();
    initscr();
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    init_pair(4,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(5,COLOR_CYAN,COLOR_BLACK);

    noecho();
    clear();
    int R = LINES/2;
    int xo = COLS/2;
    int yo = LINES/2;
    int SIDE = 5;
    // fractal_generate(stdscr,10);
    for(int i=3; i <10; i++)
    {
        fractal_generate(stdscr,i);
        Sleep(2000);
        clear();
    }



    refresh();
    getch();
    return 0;
}
void fractal_generate(WINDOW* win, unsigned int size)
{
    int MAX_COLS;
    int MAX_ROWS;
    vert polygon[30];
    getmaxyx(win,MAX_ROWS,MAX_COLS);
    int SIDES = size;
    int R = MAX_ROWS/2;
    int xo = MAX_COLS/2;
    int yo = MAX_ROWS/2;

    for(int i =0; i < SIDES;i++)
    {
        float angle = (360/size)*i;
        angle = (M_PI/180)*angle;
        float angle_y = yo+sin(angle)*R;
        float angle_x = xo+cos(angle)*COLS/3;

        vert v;
        v.x = angle_x;
        v.y = angle_y;
        polygon[i] = v;
        wmove(win,angle_y,angle_x);
        waddch(win,'.');
    }
    wrefresh(win);

    int index;
    int xi = randombytes_random()%R;
    int yi = randombytes_random()%R;

    wmove(win,yi,xi);
    waddch(win,'.');
    for(int i=0;i <MAX_ITER;i++)
    {
        index = randombytes_random()%size;
        if(size>3)
        {
            xi = xi+((polygon[index].x-xi)*2)/3;
            yi = yi+((polygon[index].y-yi)*2)/3;
        }
        else
        {
            xi = (xi+polygon[index].x)/2;
            yi = (yi+polygon[index].y)/2;
        }
        wmove(win,yi,xi);
        switch (index)
        {
        case 0:
        {
            wattron(win,COLOR_PAIR(1));
            break;
        }
        case 1:
        {
            wattron(win,COLOR_PAIR(2));
            break;
        }
        case 2:
        {
            wattron(win,COLOR_PAIR(3));
            break;
        }
        case 3:
        {
            wattron(win,COLOR_PAIR(4));
            break;
        }
        case 4:
        {
            wattron(win,COLOR_PAIR(5));
            break;
        }
        
        default:
            break;
        }
        waddch(win,'.');
        wrefresh(win);


    }
    



}