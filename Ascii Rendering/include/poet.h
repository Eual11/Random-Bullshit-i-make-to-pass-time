#include <curses.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif
#include <stdio.h>
#define START_COMMAND 0
#define END_COMMAND 1
#define CLEAR_COMMAND 2
#define DELAY_COMMAND 3

/*COLORS*/
#define BLACK_AND_WHITE 1
#define BLACK_AND_RED 2
#define CYAN_AND_BLACK 3
#define WHITE_AND_BLUE 4
#define M_PI 3.14159265358979323846
#define GREEN_AND_BLACK 5
typedef struct WinState
{
    WINDOW* win;
    int curX;
    int curY;
    bool full;
} WinState;
typedef struct vect
{
    int x;
    int y;
} vert;

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
WinState* poet(WinState* cur_state,const char* text,int size);
/*
    convienent wait function
*/
void wait(float sec);
/*this function distroys the given window and clears it*/
void destroy_window(WINDOW* win);

/*
this function accepts a string array and displays it with a credit roll effect
*/
WinState* credit_roll(WinState* cur_state,char** credit_txt,int size);

/*
the infamous ascii_renderer
*/
WinState* ascii_render(WinState* cur_state, char* ascii_buffer);

void COMPOSE(WINDOW* msg_win, WINDOW* credits_win, WINDOW* ascii_win, char* filename);
void fractal_generate(WINDOW* win, unsigned int size);
int make_worms(WINDOW *g_win);