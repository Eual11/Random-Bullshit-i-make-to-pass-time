#include <curses.h>
#include <stdlib.h>

#define MAX_ITER 1000

int main(int argc, char **argv)
{

    int max_cols, max_rows;
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, true);
    start_color();
    max_cols = COLS - 1;
    max_rows = LINES - 1;
    double xf = 2.0;
    double xi = -2.0;
    double yi = 2.0;
    double yf = -2.0;
    int ch = EOF;
    while (1)
    {
        ch = EOF;
        for (int x = 0; x <= max_cols; x++)
        {
            for (int y = 0; y < max_rows; y++)
            {
                double cx = ((xf - xi) * x / (double)(max_cols)) + xi;
                double cy = ((yf - yi) * y / (double)(max_rows) + yi);

                double zx = 0;
                double zy = 0;
                int iter = 0;
                while (((zx * zx) + (zy * zy) <= 4) && iter < MAX_ITER)
                {
                    double ztmp = (zx * zx) - (zy * zy) + cx;
                    zy = 2 * zx * zy + cy;
                    zx = ztmp;
                    iter++;
                }
                ",-~:;=!*#$@";

                if (iter == MAX_ITER)
                {
                    mvaddch(y, x, '*');
                }
                else if(iter>800)
                {
                    mvaddch(y, x, '-');
                }
                else if(iter>600)
                {
                    mvaddch(y, x, '~');
                }
                else if(iter>400)
                {
                    mvaddch(y, x, ',');
                }

                else 
                {
                    mvaddch(y, x, '.');

                }

                refresh();
            }
        }

        ch = getch();
        if (ch == 27)
        {
            break;
        }
        else if (ch == KEY_LEFT)
        {
            xf -= 0.005;
            xi -= 0.005;
        }
        else if (ch == KEY_RIGHT)
        {
            xf += 0.005;
            xi += 0.005;
        }
        else if(ch == KEY_UP)
        {
            yf -= 0.005;
            yi -= 0.005;
        }
        else if(ch == KEY_DOWN)
        {
            yf += 0.005;
            yi += 0.005;
        }
        else if(ch == 'z')
        {
            xi = (xf-xi)/100+xi;
            xf = (xi-xf)/100+xf;

            yi = yi-(yi-yf)/100;
            yf = yf-(yf-yi)/100;


        }
        else if(ch == 'a')
        {
            xi = -(xf-xi)/100+xi;
            xf = -(xi-xf)/100+xf;
             yi = (yi-yf)/100+yi;
            yf = (yf-yi)/100+yf;


        }
    }

    // getch();
    return 0;
}
