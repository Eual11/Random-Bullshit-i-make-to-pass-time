#include <curses.h>
#include <math.h>
const int MAX_ITER = 10000;
int main(int argc, char **argv)
{
    // this is a triumph
    initscr();
    start_color();
    noecho();
    clear();
    int max_cols, max_rows;
    max_cols = COLS - 1;
    max_rows = LINES - 1;
    int x = 0;
    int y = 0;
    // for(; iter<MAX_ITER;)
    for (int x = 0; x < max_cols; x++)
    {
        for (int y = 0; y < max_rows; y++)
        {
            double cx = (4.0 / (max_cols) * (x)) - 2;
            double cy = (-4.0 / (float)max_rows) * y + 2;
            int iter = 0;
            double xo = 0;
            double yo = 0;
            iter = 0;
            while (((xo * xo) + (yo * yo) <= 4.0) && (iter < MAX_ITER))
            {
                double xtemp = (xo * xo) - (yo * yo) + cx;
                yo = 2.0 * xo * yo + cy;
                xo = xtemp;
                ++iter;
                // printf("inflooped\n");
            }
            // printf("out\n");
            char pnt = ",-~:;=!*#$@"[iter%12];
            if (iter == MAX_ITER)
            {
                mvaddch(y, x, pnt);
            }
            else if (iter > 600)
            {
                mvaddch(y, x, pnt);
            }
            else if (iter > 400)
            {
                mvaddch(y, x, pnt);
            }
            else
            {
                mvaddch(y, x, '.');
            }

            refresh();
        }
    }

    getch();

    return 0;
}