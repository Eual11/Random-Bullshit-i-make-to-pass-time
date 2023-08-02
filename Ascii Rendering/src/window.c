#include <curses.h>

WINDOW* create_window(int height, int width, int x, int y);
void destroy_window(WINDOW* win);

int main(int argc, char**argv)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    int startx, starty;
    int ch;
    int width = 10;// width of the new widow
    int height = 3; //height of the new window

    starty = (LINES-height)/2; //starting position at start, basically at the center 
    startx = (COLS-width)/2; //starting position at start, at the center

    printw("Press F1 to Close the Window LINES"); //prompts the user what button to click to exit
    refresh(); //writes into the windows from the buffer  treescrn =
    WINDOW* win = create_window(height,width,startx,starty);
    while((ch=getch())!=KEY_F(1))
    {
        switch(ch)
        {
            case KEY_LEFT:
            {
                destroy_window(win);
                win = create_window(height,width,--startx,starty);
                break;
            }
            case KEY_RIGHT:
            {
                destroy_window(win);
                win = create_window(height,width,++startx,starty);
                break;
            }
            case KEY_UP:
            {
                destroy_window(win);
                win = create_window(height,width, startx,--starty);
                break;
            }
            case KEY_DOWN:
            {
                if(starty<LINES-height)
                {
                    destroy_window(win);
                    win = create_window(height,width,startx,++starty);
                }
                 break;

            }
        }
    }


    endwin();
    return 0;
}
WINDOW* create_window(int height, int width, int x, int y)
{
    WINDOW* win =  newwin(height,width,y,x);
   if(win)
   {
     box(win,0,0);
    wrefresh(win);
    return win;
   }
   else
   {
    // printw("Cannot Create New WIndow \n");
    return NULL;
   }

}
    
void destroy_window(WINDOW* win)
{
    wborder(win,' ',' ',' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);
}