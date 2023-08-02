#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sodium.h>
#include <Windows.h>

typedef struct vert
{
    int x;
    int y;
    /* data */
} vert;
const int MAX_ITER = 1000000;
int maxcols,maxrows;

vert triangle[3];

int main(int argc, char** argv)
{
    initscr();
    start_color();
    noecho();
    nocbreak();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    clear();

    maxcols = COLS-1;
    maxrows = LINES-1;
    int index;
    triangle[0].x = 0;
    triangle[0].y = 0;
    triangle[1].x = maxcols/2;
    triangle[1].y = maxrows;
    triangle[0].x = maxcols;
    triangle[0].y = 0;
    mvaddch(triangle[0].y,triangle[0].x,'2');
    mvaddch(triangle[1].y,triangle[1].x,'1');
    mvaddch(triangle[2].y,triangle[2].x,'0');
    

    int xi, yi;
    srand(time(NULL));
    xi = rand()%maxcols;
    yi = rand()%maxrows;
    mvaddch(yi, xi, '.');
    for(int i =0; i < MAX_ITER; i++)
    {
        srand(i);
        index = randombytes_random()%3;
        xi = (xi+triangle[index].x)/2;
        yi= (yi+triangle[index].y)/2;
        Sleep(0.006*1000);
        switch (index)
        {
        case 0:
        {
            attron(COLOR_PAIR(1));
            break;
        }
        case 1:
        {
            attron(COLOR_PAIR(2));
            break;
        }
        case 2:
        {
            attron(COLOR_PAIR(3));
        }
        
        default:
            break;
        }
        // attron(COLOR_PAIR(3));
        mvaddch(yi,xi,'.');
        refresh();

        // mvprintw(yi,xi,"%d",index);

    }
   while(true){

   }

    




    return 0;
}

