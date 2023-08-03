#include "../include/poet.h"
#include <sodium.h>
#define FLAVORS 7

chtype flavor[FLAVORS] =
    {
        'O', '*', '#', '$', '%', '0', '@'};

const short winc[] =
    {
        1, 1, 1, 0, -1, -1, -1, 0},
            yinc[] =
                {
                    -1, 0, 1, 1, 1, 0, -1, -1};
struct worm
{
    int orientation, head;
    short *xpos, *ypos;
} worm[40];

const char *field;
//  int length = 16, number = 3;
chtype trail = ' ';

const struct options
{
    int nopts;
    int opts[3];
} normal[8] =
    {
        {3, {7, 0, 1}}, {3, {0, 1, 2}}, {3, {1, 2, 3}}, {3, {2, 3, 4}}, {3, {3, 4, 5}}, {3, {4, 5, 6}}, {3, {5, 6, 7}}, {3, {6, 7, 0}}},
  upper[8] =
      {
          {1, {1, 0, 0}}, {2, {1, 2, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {2, {4, 5, 0}}, {1, {5, 0, 0}}, {2, {1, 5, 0}}},
  left[8] =
      {
          {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {2, {2, 3, 0}}, {1, {3, 0, 0}}, {2, {3, 7, 0}}, {1, {7, 0, 0}}, {2, {7, 0, 0}}},
  right[8] =
      {
          {1, {7, 0, 0}}, {2, {3, 7, 0}}, {1, {3, 0, 0}}, {2, {3, 4, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {2, {6, 7, 0}}},
  lower[8] =
      {
          {0, {0, 0, 0}}, {2, {0, 1, 0}}, {1, {1, 0, 0}}, {2, {1, 5, 0}}, {1, {5, 0, 0}}, {2, {5, 6, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}},
  upleft[8] =
      {
          {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {1, {3, 0, 0}}, {2, {1, 3, 0}}, {1, {1, 0, 0}}},
  upright[8] =
      {
          {2, {3, 5, 0}}, {1, {3, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {1, {5, 0, 0}}},
  lowleft[8] =
      {
          {3, {7, 0, 1}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {1, {1, 0, 0}}, {2, {1, 7, 0}}, {1, {7, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}},
  lowright[8] =
      {
          {0, {0, 0, 0}}, {1, {7, 0, 0}}, {2, {5, 7, 0}}, {1, {5, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}, {0, {0, 0, 0}}};

static void cleanup(WINDOW *win)
{
    standend();
    wrefresh(win);
    curs_set(1);
    endwin();
}

void wait(float sec)
{
#ifdef _WIN32
    Sleep(1000 * sec);
#else
    sleep(sec);
#endif
}

void destroy_window(WINDOW *win)
{
    if (win)
    {
        delwin(win);
        wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(win);
    }
    else
    {
        fprintf(stderr, "Cannot Destroy window \n");
    }
}

WINDOW *create_window(int x, int y, int width, int height)
{
    WINDOW *win = NULL;
    win = newwin(height, width, y, x);

    if (win)
    {
        box(win, 0, 0);
        wrefresh(win);
        return win;
    }
    else
    {
        fprintf(stderr, "ERROR: Cannot Create Window\n");
        return NULL;
    }
}

void COMPOSE(WINDOW *msg_win, WINDOW *credits_win, WINDOW *ascii_win, char *filename)
{
    FILE *fptr = NULL; // file pointer
    int rch;
    char buffer[1024];
    WinState *cur_state = malloc(sizeof(WinState)); // curent state of program
    WINDOW *cur_win = NULL;
    char *ext = ".bez";
    char win_name[10];
    win_name[9] = '\0';
    char command[10];
    command[9] = '\0';
    int command_num = -1;
    char *tmpname = filename;
    int len = strlen(filename);
    float DELAY = 0;
    if (strcmp((tmpname + (len - 4)), ext))
    {
        fprintf(stderr, "ERROR: Invalid Extention. Please Make Sure the file is .bez extention\n");
        return;
    }

    fptr = fopen(filename, "r");

    if (!fptr)
    {
        fprintf(stderr, "ERROR file %s doesn't exist \n", filename);
        return;
    }
    int cindex = 0;
    while ((rch = fgetc(fptr)) != EOF)
    {
        command[cindex] = rch;
        if (strncmp(command, "END", 3) == 0)
        {
            memset(command, ' ', 9);
            command[9] = '\0';
            rch = fgetc(fptr);
            if (rch != ' ')
            {
                fprintf(stdout, "Syntax Error, a space expected after a command\n");
                return;
            }
            cindex = 0;
            command_num = END_COMMAND;
            command[9] = '\0';
        }
        else if (strncmp(command, "CLEAR", 5) == 0)
        {
            rch = fgetc(fptr);
            if (rch != ' ')
            {
                fprintf(stderr, "Syntax Error, a space expected after a command\n");
                return;
            }
            memset(command, ' ', 9);
            cindex = 0;
            command_num = CLEAR_COMMAND;
            command[9] = '\0';
        }
        else if ((strncmp(command, "START", 5)) == 0)
        {

            rch = fgetc(fptr);
            if (rch != ' ')
            {
                fprintf(stderr, "Syntax Error, a space expected after a command\n");
                return;
            }
            else
            {
                memset(command, ' ', 9);
                command[9] = '\0';
                cindex = 0;
                command_num = START_COMMAND;
            }
        }

        else if ((strncmp(command, "DELAY", 5)) == 0)
        {
            rch = fgetc(fptr);
            if (rch != ' ')
            {
                fprintf(stderr, "Syntax Error, a space expected after a command\n");
                return;
            }
            else
            {
                memset(command, '-', 9);
                command[9] = '\0';
                cindex = 0;
                char n[3];
                n[0] = fgetc(fptr);
                n[1] = fgetc(fptr);
                n[2] = '\0';
                DELAY = atof(n);
                printf("%s", n);
                command_num = DELAY_COMMAND;
            }
        }

        else if (cindex > 5 && command_num == -1)
        {
            printf(" UNKOWN COMMAND:%s\n", command);

            return;
        }
        else
        {
            cindex++;
            cindex = cindex >= 9 ? 0 : cindex;
        }

        switch (command_num)
        {
        case START_COMMAND:
        {
            command_num = -1;
            cindex = 0;
            fread(win_name, sizeof(char), 4, fptr);
            if ((strncmp(win_name, "MSG", 3) == 0))
            {
                cur_win = msg_win;
                fprintf(stderr, "Start command on MSG win\n");
            }
            else if ((strncmp(win_name, "CRE", 3) == 0))
            {
                cur_win = credits_win;
                fprintf(stderr, "Start command on CRE win\n");
            }
            else if ((strncmp(win_name, "ASC", 3) == 0))
            {
                cur_win = ascii_win;
                fprintf(stderr, "Start command on ASC win\n");
            }
            else
            {
                fprintf(stderr, "Unknown Window Used on Start Command %s \n", win_name);
                return;
            }
            // memset(win_name,' ',9);

            break;
        }
        case END_COMMAND:
        {
            command_num = -1;
            cindex = 0;
            fread(win_name, sizeof(char), 4, fptr);
            if ((strncmp(win_name, "MSG", 3) == 0))
            {
                cur_win = NULL;
                fprintf(stderr, "END command on MSG win\n");
            }
            else if ((strncmp(win_name, "CRE", 3) == 0))
            {
                cur_win = NULL;
                fprintf(stderr, "END command on CRE win\n");
            }
            else if ((strncmp(win_name, "ASC", 3) == 0))
            {
                cur_win = NULL;
                fprintf(stderr, "END command on ASC win\n");
            }
            else
            {
                fprintf(stderr, "Unknown Window Used on END Command%s\n", win_name);
                return;
            }
            // memset(win_name,' ',9);

            break;
        }

        case CLEAR_COMMAND:
        {
            command_num = -1;
            cindex = 0;
            cur_win = NULL;
            fread(win_name, sizeof(char), 4, fptr);
            if ((strncmp(win_name, "MSG", 3) == 0))
            {
                wclear(msg_win);
                wborder(msg_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                box(msg_win, 0, 0);
                wrefresh(msg_win);
                fprintf(stdout, "CLEAR command on MSG win\n");
            }
            else if ((strncmp(win_name, "CRE", 3) == 0))
            {
                wclear(credits_win);
                wborder(credits_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                box(credits_win, 0, 0);
                wrefresh(msg_win);
                fprintf(stdout, "CLEAR command on CRE win\n");
            }
            else if ((strncmp(win_name, "ASC", 3) == 0))
            {
                wclear(ascii_win);
                wborder(ascii_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                box(ascii_win, 0, 0);
                wrefresh(ascii_win);
                fprintf(stdout, "CLEAR command on ASC win\n");
            }
            else
            {
                fprintf(stderr, "Unknown Window Used on CLEAR Command\n");
                return;
            }
            // memset(win_name,' ',9);

            break;
        }

        case DELAY_COMMAND:
        {
            printf("delayed for %f\n", DELAY);
            wait(DELAY);
            command_num = -1;
            break;
        }
        }

        if (cur_win)
        {
            char text[2048];
            int txt_ptr = 0;
            if (cur_win == msg_win || cur_win == ascii_win)
            {
                bool start = false;
                bool end = false;
                cur_state->win = cur_win;

                if ((rch = fgetc(fptr)) != '~')
                {
                    printf("NO %c start tilde\n", rch);
                    return;
                }
                else
                {
                    start = true;
                }
                while (start)
                {
                    rch = fgetc(fptr);
                    if (rch == '&')
                    {
                        fgetc(fptr);
                        if (txt_ptr < 2046)
                        {
                            text[txt_ptr++] = '\\';
                            text[txt_ptr++] = 'n';
                        }
                        rch = fgetc(fptr);

                        if (rch != '~')
                        {
                            start = false;
                            fseek(fptr, -1L, SEEK_CUR);
                            cur_win = NULL;

                            poet(cur_state, text, txt_ptr);
                            memset(text, '\0', 2048);

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

            else if (cur_win == credits_win)
            {
                char *text_arr[100];
                int size = 0;
                int txt_ptr = 0;
                cur_state->win = cur_win;
                int width = cur_win->_maxx;
                // char credit[width];
                char *credit = calloc(width, sizeof(char));

                bool start = false;
                if ((rch = fgetc(fptr)) != '~')
                {
                    printf("NO %c start tilde\n", rch);
                    return;
                }
                else
                {
                    start = true;
                }
                while (start)
                {
                    rch = fgetc(fptr);
                    if (rch == '&')
                    {
                        fgetc(fptr);
                        if (size < 100)
                        {
                            text_arr[size] = credit;
                            size++;
                            // memset(credit,'\0',width);
                            credit = calloc(80, sizeof(char));
                            txt_ptr = 0;
                        }

                        rch = fgetc(fptr);
                        if (rch != '~')
                        {
                            start = false;
                            fseek(fptr, -1, SEEK_CUR);
                            cur_win = NULL;
                            // printf("the credit: %s \n", text_arr[1]);
                            credit_roll(cur_state,text_arr,size);

                            break;
                        }
                    }
                    else
                    {
                        if (txt_ptr >= width - 1)
                        {
                            credit[txt_ptr] = '\0';
                        }
                        else
                        {
                            credit[txt_ptr] = rch;
                            txt_ptr++;
                        }
                    }
                }
            }
            else if (cur_win == ascii_win)
            {
                // fprintf(stdout,"%c",rch);
            }
        }
    }

    return;
}
WinState *poet(WinState *cur_state, const char *c, int size)
{
    int xinit;
    int yinit;
    getyx(cur_state->win, yinit, xinit);
    ++xinit, ++yinit;
    if ((xinit && yinit))
    {
        xinit = 1;
    }
    int x = xinit;
    int y = yinit;
    int MAX_ROW, MAX_COL;
    getmaxyx(cur_state->win, MAX_ROW, MAX_COL);
    int prev = EOF;
    int ch;
    bool escape_mode = false;
    if (cur_state->full)
    {
        wclear(cur_state->win);
        xinit = cur_state->win->_begx;
        yinit = cur_state->win->_begy;
        x = xinit;
        y = xinit;
        cur_state->full = false;
        box(cur_state->win, 0, 0);
    }
    for (int i = 0; i < size; i++)
    {
        ch = c[i];
        if (y >= MAX_ROW - 1)
        {
            attron(A_BOLD);
            attron(A_STANDOUT);
            wait(2);
            getch();
            wrefresh(cur_state->win);
            attroff(A_BOLD);
            attroff(A_STANDOUT);
            wmove(cur_state->win, yinit, xinit);
            wclear(cur_state->win);
            cur_state->full = true;

            x = cur_state->win->_begx + 1;
            y = cur_state->win->_begy + 1;
            box(cur_state->win, 0, 0);
        }
        if (x >= MAX_COL - 3)
        {
            ++y;
            x = xinit;
            wmove(cur_state->win, y, x);
        }
        if (prev == '\\' || ch == '\\')
        {
            escape_mode = true;
            switch (ch)
            {
            case 'n':
            {
                ++y;
                x = xinit;
                wmove(cur_state->win, y, x);
                break;
            }
            case '1':
            {
                wattroff(cur_state->win, getattrs(cur_state->win));
                wattron(cur_state->win, COLOR_PAIR(BLACK_AND_WHITE));
                break;
            }
            case '2':
            {
                wattroff(cur_state->win, getattrs(cur_state->win));
                wattron(cur_state->win, COLOR_PAIR(BLACK_AND_RED));
                break;
            }
            case '3':
            {
                wattroff(cur_state->win, getattrs(cur_state->win));
                wattron(cur_state->win, COLOR_PAIR(CYAN_AND_BLACK));
                break;
            }
            case '4':
            {
                wattroff(cur_state->win, getattrs(cur_state->win));
                wattron(cur_state->win, COLOR_PAIR(WHITE_AND_BLUE));
                break;
            }
            case '5':
            {
                wattroff(cur_state->win, getattrs(cur_state->win));
                wattron(cur_state->win, COLOR_PAIR(GREEN_AND_BLACK));
                break;
            }
            case 'a':
            {

                wattron(cur_state->win, A_ALTCHARSET);
                break;
            }
            case 'i':
            {
                wattron(cur_state->win, A_INVIS);
                break;
            }
            case 'p':
            {
                wattron(cur_state->win, A_PROTECT);
                break;
            }
            case 'b':
            {
                wattron(cur_state->win, A_BOLD);
                break;
            }
            case 'd':
            {
                wattron(cur_state->win, A_DIM);
                break;
            }
            case 'l':
            {
                wattron(cur_state->win, A_BLINK);
                break;
            }
            case 'r':
            {
                wattron(cur_state->win, A_REVERSE);
                break;
            }
            case 'u':
            {
                wattron(cur_state->win, A_UNDERLINE);
                break;
            }
            case 'x':
            {
                wattron(cur_state->win, A_STANDOUT);
                break;
            }
            case 'z':
            {
                wattron(cur_state->win, A_NORMAL);
                break;
            }
            default:
                break;
            }
        }
        if (!escape_mode)
        {
            mvwprintw(cur_state->win, y, x, "%lc", ch);
            // wait(0.1);
        }

        x++;
        wrefresh(cur_state->win);
        prev = ch;
        escape_mode = false;
    }
    return cur_state;
}
int main(int argc, char **argv)
{
    printf("Please Make Sure To make your Terminal is in fullscreen :)");
    getchar();
    initscr(); // initalized stdscr
    noecho();  // disables the annoying echoing of getch();
    cbreak();
    start_color(); // enables color support
    // init_pair(1,COLOR_BLACK,COLOR_WHITE); //first color pair
    // curs_set(0);
    // init_pair(2,COLOR_RED,COLOR_BLACK); //first color pair
    // init_pair(3,COLOR_CYAN,COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    // init_pair(5,COLOR_BLACK,COLOR_GREEN);
    // curs_set(0);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    // init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    keypad(stdscr, true); // maybe if i need keyboard input
    int margin = 1;
    int MAX_ROW, MAX_COL;
    int ch;
    WINDOW *msg_win;
    WINDOW *credits_win;
    WINDOW *ascii_win;
    getmaxyx(stdscr, MAX_ROW, MAX_COL); // inquires the terminal for the maximum ROWs and COLs

    int msg_win_startX = 0; // the msg window is supposed to start at the very begineing of the screen
    int msg_win_startY = 0;
    int msg_win_width = (int)(0.40 * MAX_COL);                        // the msg window spans only 40% od the full width
    int msg_win_height = MAX_ROW;                                     // the height is the total screen height
    int credits_win_startX = msg_win_startX + msg_win_width + margin; // the credit window start position is translated by the width of msg window plus a margin given above
    int credits_win_startY = msg_win_startY;
    int credits_win_width = msg_win_width; // the credits window is as wide as the msg window but only half of the its height
    int credits_win_height = msg_win_height / 2;

    int ascii_win_startX = msg_win_startX + msg_win_width + margin; // asci window starts at the position of credits window but translated by the height of credits window + margin
    int ascii_win_startY = credits_win_startY + credits_win_height;
    int ascii_win_width = msg_win_width; // full width of msg window but half of its window
    int ascii_win_height = msg_win_height / 2;

    refresh(); // refreshes stdstr
    msg_win = create_window(msg_win_startX, msg_win_startY, msg_win_width, msg_win_height);
    ascii_win = create_window(ascii_win_startX, ascii_win_startY, ascii_win_width, ascii_win_height);
    credits_win = create_window(credits_win_startX, credits_win_startY, credits_win_width, credits_win_height);
    wrefresh(ascii_win);
    COMPOSE(msg_win, credits_win, ascii_win, "program.bez");
    while (true)
    {
    }
    return 0;
}
void fractal_generate(WINDOW *win, unsigned int size)
{
    int MAX_COLS;
    int MAX_ROWS;
    vert polygon[30];
    getmaxyx(win, MAX_ROWS, MAX_COLS);
    int SIDES = size;
    int R = MAX_ROWS / 2;
    int xo = MAX_COLS / 2;
    int yo = MAX_ROWS / 2;
    int MAX_ITER = 50000;

    for (int i = 0; i < SIDES; i++)
    {
        float angle = (360 / size) * i;
        angle = (M_PI / 180) * angle;
        float angle_y = yo + sin(angle) * R;
        float angle_x = xo + cos(angle) * COLS / 3;

        vert v;
        v.x = angle_x;
        v.y = angle_y;
        polygon[i] = v;
        wmove(win, angle_y, angle_x);
        waddch(win, '.');
    }
    wrefresh(win);

    int index;
    int xi = randombytes_random() % R;
    int yi = randombytes_random() % R;

    wmove(win, yi, xi);
    waddch(win, '.');
    for (int i = 0; i < MAX_ITER; i++)
    {
        index = randombytes_random() % size;
        if (size > 3)
        {
            xi = xi + ((polygon[index].x - xi) * 2) / 3;
            yi = yi + ((polygon[index].y - yi) * 2) / 3;
        }
        else
        {
            xi = (xi + polygon[index].x) / 2;
            yi = (yi + polygon[index].y) / 2;
        }
        wmove(win, yi, xi);
        switch (index)
        {
        case 0:
        {
            wattron(win, COLOR_PAIR(1));
            break;
        }
        case 1:
        {
            wattron(win, COLOR_PAIR(2));
            break;
        }
        case 2:
        {
            wattron(win, COLOR_PAIR(3));
            break;
        }
        case 3:
        {
            wattron(win, COLOR_PAIR(4));
            break;
        }
        case 4:
        {
            wattron(win, COLOR_PAIR(5));
            break;
        }
        case 5:
        {
            wattron(win, COLOR_PAIR(6));
            break;
        }

        default:
            break;
        }
        waddch(win, '.');
        wrefresh(win);
    }
}
int make_worms(WINDOW *g_win)
{
    const struct options *op;
    struct worm *w;
    short **ref, *ip;
    time_t seed;
    int x, y, n, h, last, bottom;

#ifdef XCURSES
    Xinitscr(argc, argv);
#else
    int number = 20;
    int length = 16;

#endif
    seed = time((time_t *)0);
    srand(seed);

    WINDOW *win = g_win;

    bottom = LINES - 1;
    last = COLS - 1;

#ifdef A_COLOR
    if (has_colors())
    {
        short bg = COLOR_BLACK;
        start_color();

#if defined(NCURSES_VERSION) || (defined(PDC_BUILD) && PDC_BUILD > 3000)
        if (use_default_colors() == OK)
            bg = -1;
#endif

#define SET_COLOR(num, fg)      \
    init_pair(num + 1, fg, bg); \
    flavor[num] |= COLOR_PAIR(num + 1) | A_BOLD

        SET_COLOR(0, COLOR_GREEN);
        SET_COLOR(1, COLOR_RED);
        SET_COLOR(2, COLOR_CYAN);
        SET_COLOR(3, COLOR_WHITE);
        SET_COLOR(4, COLOR_MAGENTA);
        SET_COLOR(5, COLOR_BLUE);
        SET_COLOR(6, COLOR_YELLOW);
    }
#endif

    ref = malloc(sizeof(short *) * LINES);

    for (y = 0; y < LINES; y++)
    {
        ref[y] = malloc(sizeof(short) * COLS);

        for (x = 0; x < COLS; x++)
            ref[y][x] = 0;
    }

#ifdef BADCORNER
    /* if addressing the lower right corner doesn't work in your curses */

    ref[bottom][last] = 1;
#endif

    for (n = number, w = &worm[0]; --n >= 0; w++)
    {
        w->orientation = w->head = 0;

        if ((ip = malloc(sizeof(short) * (length + 1))) == NULL)
        {
            // fprintf(stderr, "%s: out of memory\n", *argv);
            return EXIT_FAILURE;
        }

        w->xpos = ip;

        for (x = length; --x >= 0;)
            *ip++ = -1;

        if ((ip = malloc(sizeof(short) * (length + 1))) == NULL)
        {
            // fprintf(stderr, "%s: out of memory\n", *argv);
            return EXIT_FAILURE;
        }

        w->ypos = ip;

        for (y = length; --y >= 0;)
            *ip++ = -1;
    }

    if (field)
    {
        const char *p = field;

        for (y = bottom; --y >= 0;)
            for (x = COLS; --x >= 0;)
            {
                // addch((chtype) (*p++));
                waddch(win, (chtype)(*p++));
                if (!*p)
                    p = field;
            }
    }

    napms(12);
    wrefresh(win);
    nodelay(win, TRUE);

    for (;;)
    {
        int ch;

        if (true)
        {
#ifdef KEY_RESIZE
            if (ch == KEY_RESIZE)
            {
#ifdef PDCURSES
                resize_term(0, 0);
#endif
                if (last != COLS - 1)
                {
                    for (y = 0; y <= bottom; y++)
                    {
                        ref[y] = realloc(ref[y], sizeof(short) * COLS);

                        for (x = last + 1; x < COLS; x++)
                            ref[y][x] = 0;
                    }

                    last = COLS - 1;
                }

                if (bottom != LINES - 1)
                {
                    for (y = LINES; y <= bottom; y++)
                        free(ref[y]);

                    ref = realloc(ref, sizeof(short *) * LINES);

                    for (y = bottom + 1; y < LINES; y++)
                    {
                        ref[y] = malloc(sizeof(short) * COLS);

                        for (x = 0; x < COLS; x++)
                            ref[y][x] = 0;
                    }

                    bottom = LINES - 1;
                }
            }

#endif /* KEY_RESIZE */

            /* Make it simple to put this into single-step mode,
               or resume normal operation - T. Dickey */

            if (ch == 'q')
            {
                cleanup(win);
                return EXIT_SUCCESS;
            }
            else if (ch == 's')
                nodelay(win, FALSE);
            else if (ch == ' ')
                nodelay(win, TRUE);
        }

        for (n = 0, w = &worm[0]; n < number; n++, w++)
        {
            if ((x = w->xpos[h = w->head]) < 0)
            {
                // move(y = w->ypos[h] = bottom, x = w->xpos[h] = 0);
                wmove(win, y = w->ypos[h] = bottom, x = w->xpos[h] = 0);
                waddch(win, flavor[n % FLAVORS]);
                // addch(flavor[n % FLAVORS]);
                ref[y][x]++;
            }
            else
                y = w->ypos[h];

            if (x > last)
                x = last;

            if (y > bottom)
                y = bottom;

            if (++h == length)
                h = 0;

            if (w->xpos[w->head = h] >= 0)
            {
                int x1 = w->xpos[h];
                int y1 = w->ypos[h];

                if (y1 < LINES && x1 < COLS && --ref[y1][x1] == 0)
                {
                    // move(y1, x1);
                    wmove(win, y1, x1);
                    waddch(win, trail);
                    // addch(trail);
                }
            }

            op = &(x == 0 ? (y == 0 ? upleft : (y == bottom ? lowleft : left)) : (x == last ? (y == 0 ? upright : (y == bottom ? lowright : right)) : (y == 0 ? upper : (y == bottom ? lower : normal))))
                     [w->orientation];

            switch (op->nopts)
            {
            case 0:
                cleanup(win);
                return EXIT_SUCCESS;
            case 1:
                w->orientation = op->opts[0];
                break;
            default:
                w->orientation = op->opts[rand() % op->nopts];
            }

            // move(y += yinc[w->orientation], x += winc[w->orientation]);
            wmove(win, y += yinc[w->orientation], x += winc[w->orientation]);

            if (y < 0)
                y = 0;

            // addch(flavor[n % FLAVORS]);
            waddch(win, flavor[n % FLAVORS]);
            ref[w->ypos[h] = y][w->xpos[h] = x]++;
        }
        napms(12);
        wrefresh(win);
    }
}
WinState *credit_roll(WinState *cur_state, char **credit_txt, int size)
{
    int xstart = 1;
    WINDOW *win = cur_state->win;
    int ystart = win->_maxy - 2;
    int x = xstart;
    int y = ystart;
    int y_min = 1;
    for (int i = 0; i < size; i++)
    {
        y_min += 1;
        x = xstart;
        y = ystart;
        int length = strlen(credit_txt[i]);
        while (y >= y_min)
        {
            x = xstart;
            if (y < ystart)
            {
                int pst = y + 1;

                for (int i = 0; i < length; i++)
                {
                    mvwprintw(win, pst, x, "%c", ' ');
                    x++;
                    wrefresh(win);
                }
            }
            x = xstart;

            for (int j = 0; j < length; j++)
            {
                mvwaddch(win, y, x, credit_txt[i][j]);
                x++;
            }

            x = xstart;
            y--;
            wrefresh(win);
            wait(0.2);
        }
    }
}