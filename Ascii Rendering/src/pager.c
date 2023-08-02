#include <curses.h>

int main(int argc, char** argv)
{
   int ch;
   int prev = EOF;
   int row, column;
   int x, y;
   FILE *fptr;
   if(argc!=2)
   {
      // printf("Usage: %s <filename>\n",argv[0]);
      // return 1;
   }
   fptr = fopen("program.txt","r");

   if(!fptr)
   {
      printf("Couldn't open file %s\n",argv);
      return 1;
   }

   initscr();
   // raw();
   // noecho();
   // keypad(stdscr, TRUE);
   getmaxyx(stdscr,row,column);
   y=0;
   while((ch = fgetc(fptr))!=EOF)
   {
      getyx(stdscr,y,x);
      
      if(y==row-1)
      {
         attron(A_BLINK);
         attron(A_BOLD);
         printw("Press Any Key to contniue");
         getch();
         clear();
         move(0,0);
         attroff(A_BLINK);
         attroff(A_BOLD);
      }
      if(prev == '/' && ch == '*')
      {
         move(y, x-1);
         attron(A_BOLD);
         attron(A_STANDOUT);
      }
      else if(prev == '*' && ch == '/')
      {
         move(y, x-1);
         attron(A_BOLD);
          attroff(A_STANDOUT);
      }

      else
      {
         chgat(-1, A_REVERSE, 0, NULL);
         printw("%c",ch);

      }

      prev = ch;
   
      
      refresh();
      
   }
   getch();
   endwin();

   


   return 0;
}