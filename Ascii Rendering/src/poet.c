#include "../include/poet.h"
#include <sodium.h>
void wait(float sec)
{
    #ifdef _WIN32
        Sleep(1000*sec);
    #else
        sleep(sec);
    #endif
}

void destroy_window(WINDOW* win)
{
    if(win)
    {
        delwin(win);
        wborder(win,' ',' ',' ',' ',' ',' ',' ',' ');
        wrefresh(win);
    }
    else 
    {
        fprintf(stderr,"Cannot Destroy window \n");
    }
}

WINDOW* create_window(int x, int y, int width, int height)
{
    WINDOW* win = NULL;
    win = newwin(height,width,y,x);
    
    if(win)
    {
        box(win,0,0);
        wrefresh(win);
        return win;
    }
    else
    {
        fprintf(stderr,"ERROR: Cannot Create Window\n");
        return NULL;
    }
}

void COMPOSE(WINDOW* msg_win,WINDOW* credits_win,WINDOW* ascii_win, char* filename)
{
    FILE* fptr = NULL; //file pointer
    int rch;
    char buffer[1024];
    WinState* cur_state = malloc(sizeof(WinState)); //curent state of program
    WINDOW* cur_win = NULL;
    char* ext = ".bez";
    char win_name[10];
    win_name[9] = '\0';
    char command[10];
    command[9] = '\0';
    int command_num = -1;
    char* tmpname = filename;
    int len = strlen(filename);
    float DELAY = 0;
    if(strcmp((tmpname+(len-4)),ext))
    {
        fprintf(stderr,"ERROR: Invalid Extention. Please Make Sure the file is .bez extention\n");
        return;
    }
    
    fptr = fopen(filename,"r");

    if(!fptr)
    {
        fprintf(stderr,"ERROR file %s doesn't exist \n",filename);
        return;
    }
    int cindex=0;
    while((rch=fgetc(fptr))!=EOF)
    {
        command[cindex] = rch;
       if(strncmp(command,"END",3)==0)
        {
            memset(command,' ',9); 
              command[9] = '\0';     
            rch = fgetc(fptr);
            if(rch !=' ')
            {
                fprintf(stdout,"Syntax Error, a space expected after a command\n");
                return;
            }
            cindex=0;
            command_num = END_COMMAND;
            command[9] = '\0';


        }
        else if(strncmp(command,"CLEAR",5)==0)
        {
            rch = fgetc(fptr);
            if(rch !=' ')
            {
                fprintf(stderr,"Syntax Error, a space expected after a command\n");
                return;
            }
            memset(command,' ',9);
            cindex = 0;
            command_num = CLEAR_COMMAND;
            command[9] = '\0';

        }
        else if((strncmp(command,"START",5))==0)
        {

            rch = fgetc(fptr);
            if(rch !=' ')
            {
                fprintf(stderr,"Syntax Error, a space expected after a command\n");
                return;
            }
            else
            {
                memset(command,' ',9);
                command[9] = '\0';
                cindex=0;
                command_num = START_COMMAND;   
            }
         
        }

        else if((strncmp(command,"DELAY",5))==0)
        {
            rch = fgetc(fptr);
            if(rch != ' ')
            {
                fprintf(stderr,"Syntax Error, a space expected after a command\n");
                return;
            }
            else
            {
                memset(command,'-',9);
                command[9] = '\0';
                cindex =0;
                char n[3];
                n[0] = fgetc(fptr);
                n[1] = fgetc(fptr);
                n[2] = '\0';
                DELAY = atof(n);
                printf("%s",n);
                command_num = DELAY_COMMAND;
            }

        }

        else if(cindex>5 && command_num==-1)
        {
             printf(" UNKOWN COMMAND:%s\n",command);   

            return;

        }
        else
        {
             cindex++;
             cindex=cindex>=9?0:cindex;
        }

        switch (command_num)
     {
        case START_COMMAND:
        {
            command_num = -1;
            cindex=0;
            fread(win_name,sizeof(char),4,fptr);
            if((strncmp(win_name,"MSG",3)==0))
            {
                cur_win = msg_win;
                fprintf(stderr,"Start command on MSG win\n");
            }
            else if((strncmp(win_name,"CRE",3)==0))
            {
                cur_win = credits_win;
                fprintf(stderr,"Start command on CRE win\n");

            }
            else if((strncmp(win_name,"ASC",3)==0))
            {
                cur_win = ascii_win;
                fprintf(stderr,"Start command on ASC win\n");

            }
            else
            {
                fprintf(stderr,"Unknown Window Used on Start Command\n");
                return;

            }
                // memset(win_name,' ',9);

            break;

        }
        case END_COMMAND:
        {
             command_num = -1;
             cindex=0;
             fread(win_name,sizeof(char),4,fptr);
            if((strncmp(win_name,"MSG",3)==0))
            {
                cur_win = NULL;
                fprintf(stderr,"END command on MSG win\n");
            }
            else if((strncmp(win_name,"CRE",4)==0))
            {
                cur_win = NULL;
                fprintf(stderr,"END command on CRE win\n");

            }
            else if((strncmp(win_name,"ASC",4)==0))
            {
                cur_win = NULL;
                fprintf(stderr,"END command on ASC win\n");

            }
            else
            {
                fprintf(stderr,"Unknown Window Used on Start Command\n");
                return;
            }
                // memset(win_name,' ',9);

            break;

        }

        case CLEAR_COMMAND:
        {
            command_num = -1;
            cindex=0;
            cur_win = NULL;
            fread(win_name,sizeof(char),4,fptr);
            if((strncmp(win_name,"MSG",3)==0))
            {
                wclear(msg_win);
                wborder(msg_win,' ',' ',' ',' ',' ',' ',' ',' ');
                box(msg_win,0,0);
                wrefresh(msg_win);
                fprintf(stdout,"CLEAR command on MSG win\n");

            }
            else if((strncmp(win_name,"CRE",3)==0))
            {
                wclear(credits_win);
                wborder(credits_win,' ',' ',' ',' ',' ',' ',' ',' ');
                box(credits_win,0,0);
                wrefresh(msg_win);
                fprintf(stdout,"CLEAR command on CRE win\n");


            }
            else if((strncmp(win_name,"ASC",3)==0))
            {
                wclear(ascii_win);
                wborder(ascii_win,' ',' ',' ',' ',' ',' ',' ',' ');
                box(ascii_win,0,0);
                wrefresh(ascii_win);
                fprintf(stdout,"CLEAR command on ASC win\n");



            }
            else
            {
                fprintf(stderr,"Unknown Window Used on CLEAR Command\n");
                return;

            }
                // memset(win_name,' ',9);

            break;

        }     

        case DELAY_COMMAND:
        {
            printf("delayed for %f\n",DELAY);
            wait(DELAY);
            command_num = -1;
            break;
        }   
        
    }

    if(cur_win)
    {
        char text[2048];
        int txt_ptr=0;
        cur_state->win=msg_win;
        if(cur_win==msg_win)
        {
            bool start = false;
        bool end = false;
        if((rch=fgetc(fptr))!='~')
        {
            printf("NO %c start tilde\n",rch);
            return;
        }
        else
        {
            start = true;
        }
        while(start)
        {
            rch=fgetc(fptr);
            if(rch=='&')
            {
                fgetc(fptr);
                if(txt_ptr <2046)
                    {
                        text[txt_ptr++] = '\\';
                        text[txt_ptr++] = 'n';

                    }
                rch = fgetc(fptr);

                if(rch!='~')
                {
                    start=false;
                    fseek(fptr,-1L,SEEK_CUR);
                    cur_win = NULL;

                    poet(cur_state,text,txt_ptr);
                    memset(text,'\0',2048);

                    break;
                }
            }
            else
            {
                text[txt_ptr] = rch;
                txt_ptr++;
            }
        }
        }

        else if(cur_win==credits_win)
        {
            // fprintf(stdout,"%c",rch);

        }
        else if(cur_win==ascii_win)
        {
            // fprintf(stdout,"%c",rch);

        }
    }
        
    }


    return;

}
WinState* poet(WinState* cur_state, const char* c,int size)
{
    int xinit; 
    int yinit;
    getyx(cur_state->win,yinit,xinit);
    ++xinit, ++yinit;
    if((xinit && yinit))
    {
        xinit = 1;
    }
    int x = xinit;
    int y = yinit;
    int MAX_ROW, MAX_COL;
    getmaxyx(cur_state->win,MAX_ROW,MAX_COL);
    int prev = EOF;
    int ch;
    bool escape_mode = false;
    if(cur_state->full)
    {
        wclear(cur_state->win);
        xinit =cur_state->win->_begx;
        yinit = cur_state->win->_begy;
        x = xinit;
        y = xinit;
        cur_state->full = false;
        box(cur_state->win,0,0);

    }
    for(int i=0; i <size;i++)
    {
        ch = c[i];
        if(y>=MAX_ROW-1)
        {
             attron(A_BOLD);
            attron(A_STANDOUT);
            wait(2);
           wrefresh(cur_state->win);
            attroff(A_BOLD);
            attroff(A_STANDOUT);
            wmove(cur_state->win,yinit,xinit);
            wclear(cur_state->win);
            cur_state->full = true;

            x=cur_state->win->_begx+1;
            y=cur_state->win->_begy+1;
            box(cur_state->win,0,0);

        }
        if(x>=MAX_COL-3)
        {
            ++y; 
            x = xinit;
            wmove(cur_state->win,y, x);


        }
        if(prev=='\\' || ch == '\\')
        {
            escape_mode = true;
            switch (ch)
            {
            case 'n':
            {
                ++y; 
                x = xinit;
                wmove(cur_state->win,y, x);
                break;
            }
            case '1':
            {
                wattroff(cur_state->win,getattrs(cur_state->win));
                wattron(cur_state->win,COLOR_PAIR(BLACK_AND_WHITE));
                break;
            }        
            case '2':
            {
                wattroff(cur_state->win,getattrs(cur_state->win));
                wattron(cur_state->win,COLOR_PAIR(BLACK_AND_RED));
                break;
            }    
            case '3':
            {
                wattroff(cur_state->win,getattrs(cur_state->win));
                wattron(cur_state->win,COLOR_PAIR(CYAN_AND_BLACK));
                break;

            }
            case '4':
            {
                wattroff(cur_state->win,getattrs(cur_state->win));
                wattron(cur_state->win,COLOR_PAIR(WHITE_AND_BLUE));
                break;
            }
            case '5':
            {
                wattroff(cur_state->win,getattrs(cur_state->win));
                wattron(cur_state->win,COLOR_PAIR(GREEN_AND_BLACK));
                break;
            }
            case 'a':
            {
                
                wattron(cur_state->win,A_ALTCHARSET);
                break;
            }
            case 'i':
            {
                wattron(cur_state->win,A_INVIS);
                break;
            }
            case 'p':
            {
                wattron(cur_state->win,A_PROTECT);
                break;
            }
            case 'b':
            {
                wattron(cur_state->win,A_BOLD);
                break;
            }
            case 'd':
            {
                wattron(cur_state->win,A_DIM);
                break;
            }
            case 'l':
            {
                wattron(cur_state->win,A_BLINK);
                break;
            }
            case 'r':
            {
                wattron(cur_state->win,A_REVERSE);
                break;
            }
            case 'u':
            {
                wattron(cur_state->win,A_UNDERLINE);
                break;
            }
            case 'x':
            {
                wattron(cur_state->win,A_STANDOUT);
                break;
            }
            case 'z':
            {
                wattron(cur_state->win,A_NORMAL);
                break;
            }

            default:
                break;
            }
        }
        if(!escape_mode)
        {
            mvwprintw(cur_state->win,y,x,"%lc",ch);
            wait(0.1);
        }

        x++;
        wrefresh(cur_state->win);
        prev = ch;
        escape_mode = false;

    }
    return cur_state;
}
int main(int argc, char**argv)
{
    printf("Please Make Sure To make your Terminal is in fullscreen :)");
    getchar();
    initscr(); //initalized stdscr
    noecho(); //disables the annoying echoing of getch();
    cbreak();
    start_color();//enables color support
    // init_pair(1,COLOR_BLACK,COLOR_WHITE); //first color pair
    // curs_set(0);
    // init_pair(2,COLOR_RED,COLOR_BLACK); //first color pair
    // init_pair(3,COLOR_CYAN,COLOR_BLACK);
    // init_pair(4,COLOR_BLUE,COLOR_WHITE);
    // init_pair(5,COLOR_BLACK,COLOR_GREEN);
    // curs_set(0);
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    init_pair(4,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(5,COLOR_CYAN,COLOR_BLACK);

    keypad(stdscr,true); //maybe if i need keyboard input
    int margin =1;
    int MAX_ROW, MAX_COL;
    int ch;
    WINDOW* msg_win;
    WINDOW* credits_win;
    WINDOW* ascii_win;
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
    // mvwprintw(1,1,msg_win,"I HATE MY LIFE\n");
    // mvwprintw(ascii_win,1,1,"I HATE MY LIFE");
    wrefresh(ascii_win);
    // COMPOSE(msg_win,credits_win,ascii_win,"program.bez");
    for(int i=3; i <10; i++)
    {
        clear();
        fractal_generate(stdscr,i);
        wait(2);
        wclear(stdscr);
    }
    while(true)
    {

    }
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
    int MAX_ITER = 50000;

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