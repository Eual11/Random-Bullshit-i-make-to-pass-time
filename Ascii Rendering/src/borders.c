#include <curses.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif
#include <stdio.h>
/*
    Creates a window at position x and y and the give width and height and 
    returns a pointer to that window, by default the window is surrounded by a box

    //todo, enable different boxing features
*/
WINDOW* create_window(int x, int y, int width, int height); 
/*
    Pager, this functions parses text from the given file and displays it with a typewriter effect 

    todo: a complete rehaul with new name COMPOSER
*/
void pager(WINDOW*, char[], int);
/*
    convienent wait function
*/
void wait(float sec);
/*this function distroys the given window and clears it*/
void destroy_window(WINDOW* win);

/*
this function accepts a string array and displays it with a credit roll effect
*/
void credit_roll(WINDOW* win,char** credit_txt,int size);

char* text[] ={"As far as I am concerned",
                "I resign from humanity.",
                "I no longer want to be, nor can still be, a man. ",
                "What should I do?",
                "Work for a social and political system?",
                "make a girl miserable?",
                "hunt weaknesses in a philosophical systems \0"
                "It's all too little.",
                "I renounce my humanity even though I may find myself alone"
};
int main(int argc, char** argv)
{
    printf("Make Sure to set your terminal on fullscreen Mode and Press Enter :)"); //A prompt for user to make their terminal full screen 
    getchar(); 
    int margin =1;

    int MAX_ROW, MAX_COL;
    int ch;
    WINDOW* msg_win;
    WINDOW* credits_win;
    WINDOW* ascii_win;
    initscr(); //initalized stdscr
    noecho(); //disables the annoying echoing of getch();
    cbreak();
    start_color();//enables color support
    init_pair(1,COLOR_YELLOW,COLOR_BLACK); //first color pair
    // curs_set(0);
    keypad(stdscr,true); //maybe if i need keyboard input

    getmaxyx(stdscr,MAX_ROW, MAX_COL); //inquires the terminal for the maximum ROWs and COLs

    int msg_win_startX = 0; //the msg window is supposed to start at the very begineing of the screen
    int msg_win_startY = 0; 
    int msg_win_width = (int)(0.40*MAX_COL); //the msg window spans only 40% od the full width
    int msg_win_height = MAX_ROW; //the height is the total screen height
    int credits_win_startX = msg_win_startX+msg_win_width+margin; //the credit window start position is translated by the width of msg window plus a margin given above
    int credits_win_startY = msg_win_startY; 
    int credits_win_width = msg_win_width; // the credits window is as wide as the msg window but only half of the its height
    int credits_win_height = msg_win_height/2; 

    int ascii_win_startX = msg_win_startX+msg_win_width+margin;  //asci window starts at the position of credits window but translated by the height of credits window + margin
    int ascii_win_startY = credits_win_startY+credits_win_height; 
    int ascii_win_width = msg_win_width; //full width of msg window but half of its window
    int ascii_win_height = msg_win_height/2; 

    refresh(); //refreshes stdstr
    /*
    we first create the msg_win, ascii_win, and credits_win
    */
    msg_win = create_window(msg_win_startX,msg_win_startY,msg_win_width,msg_win_height);
    ascii_win = create_window(ascii_win_startX,ascii_win_startY,ascii_win_width,ascii_win_height);
    credits_win = create_window(credits_win_startX,credits_win_startY,credits_win_width,credits_win_height);
    pager(msg_win,"program.txt",0);
    credit_roll(credits_win,text,9);

    while (true)
    {
        /* code */
    }
    
    endwin();



    return 0;
}
WINDOW* create_window(int x, int y, int width, int height)
{
    WINDOW* win =  newwin(height,width,y,x);
   if(win)
   {
     box(win,0,0);
    // wborder(win,'|','|','-','-','+','+','+','+');

    wrefresh(win);
    return win;
   }
   else
   {
    printw("Cannot Create New WIndow \n");
    return NULL;
   }

}
void destroy_window(WINDOW* win)
{
    wborder(win,' ',' ',' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);
}
void pager(WINDOW* win, char filename[], int effect)
{
    wattron(win,COLOR_PAIR(1));

    FILE* fptr = NULL;
    int xinit, yinit;
    if(!effect)
    {
    xinit = win->_begx+1;//-win->_maxx;
    yinit = win->_begy+1;//-win->_maxy;
    }
    else
    {
        xinit = win->_begx- win->_maxx+1;
        yinit = win->_begy-win->_maxy+1;
    }
    int MAX_ROW, MAX_COL;
    getmaxyx(win,MAX_ROW,MAX_COL);

    int prev = EOF;
    int ch;
    fptr = fopen(filename,"r");
    if(!fptr)
    {
        printw("couldn't open file %s", filename);
        return;
    }
    int x = xinit;
    int y = yinit;
    bool escape_mode = false;
    while((ch = fgetc(fptr)) !=EOF)
    {

        if(y>=MAX_ROW-1)
        {
            attron(A_BOLD);
            attron(A_STANDOUT);
            wprintw(win,"Press Enter");
            wgetch(win);
            wrefresh(win);
            attroff(A_BOLD);
            attroff(A_STANDOUT);
            wmove(win,yinit,xinit);
            wclear(win);

            x=xinit;
            y=yinit;
            // if(!effect)
            {
                box(win,0,0);
            }

        }
        if(x>=MAX_COL-3)
        {
            ++y; 
            x = xinit;
            wmove(win,y, x);

        }
        if(prev == '\\' || ch == '\\')
        {
            escape_mode = true;
            //entering escape character mode
            switch (ch)
            {
            case 'n':
            {
                ++y; 
                x = xinit;
                wmove(win,y, x);
                
                break;
            }
            }
        }
            if(!escape_mode)
            {
                // mvwaddch(win,y,x,ch);
                mvwprintw(win,y,x,"%lc",ch);
                wait(0.1);
            }
            prev = ch;
            escape_mode = false;


        x++;
        wrefresh(win);

    }




    
}
void wait(float sec)
{
    #ifdef _WIN32
        Sleep(1000*sec);
    #else
        sleep(sec);
    #endif
}

void credit_roll(WINDOW* win,char** credit_txt,int size)
{
    int xstart = 1;
    int ystart = win->_maxy-2;
    int x = xstart;
    int y = ystart;
    int y_min = 1;
    for(int i =0;i <size; i++)
    {
        y_min+=1;
        x=xstart;
        y=ystart;
        int length = strlen(credit_txt[i]);
        while(y>=y_min)
        {
                x=xstart;
                if(y<ystart)
                {
                 int pst = y+1;
                
                 for(int i =0; i <length; i++)
                 {
                    mvwprintw(win,pst,x,"%c",' ');
                    x++;
                    wrefresh(win);

                }
                }
                    x=xstart;

            for(int j =0; j <length; j++)
            {
                mvwaddch(win,y,x,credit_txt[i][j]);
                x++;
                
            }
            
            x=xstart;
            y--;
            wrefresh(win);
            wait(0.2);

        }

    }
    

}