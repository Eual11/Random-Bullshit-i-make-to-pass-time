#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;
using namespace std;
const int FieldHeight=20;
const int FieldWidth=10;
int Field[FieldHeight][FieldWidth]={0};
int dx=0;
bool pn=true;
bool checklines=false;
RenderWindow window(VideoMode(480,640),"Tetris", Style::Titlebar | Style::Close);
int Tetriminos[7][4] =
{
    1,3,5,7, ///I
    1,2,3,5, ///T
    2,4,5,7, // S
    3,4,5,6, ///Z
    0,1,2,3, // O
    2,4,6,7, //L
    3,5,7,6 //J
};
struct  Point
{ int x,y;   /* data */
} CPiece[4],BPiece[4];

Clock clocker;
int nr=0;
float timer=0;
bool check()
{
    for (int i=0; i<4; ++i)
    {
        if (CPiece[i].x<0 || CPiece[i].x>=FieldWidth ||CPiece[i].y>=FieldHeight)
        {
           // cout <<"happen";
            return false;
        }
        if (Field[CPiece[i].y][CPiece[i].x]) 
        {
            //cout << "it is"<<endl;
            return false;
        }
       }
        return true;
}
int main(void)
{
    
    window.setFramerateLimit(30);
    srand(time(0));
    int nCurrentPiece=rand()%7;
    bool rotate=false;
    int col=rand()%6;
    Texture tex[7];
    tex[0].loadFromFile("Assets/Blue.png");
    tex[1].loadFromFile("Assets/Green.png");
    tex[2].loadFromFile("Assets/LightBlue.png");
    tex[3].loadFromFile("Assets/Orange.png");
    tex[4].loadFromFile("Assets/Purple.png");
    tex[5].loadFromFile("Assets/Red.png");
    tex[6].loadFromFile("Assets/Yellow.png");
    Sprite SPiece;
    SPiece.setTexture(tex[col]);
    SPiece.setScale(Vector2f(0.5,0.5));
    int Score=0;
    Font pixel;
    pixel.loadFromFile("Assets/pixel.ttf");
    Text TScore;
    TScore.setFont(pixel);
    while (window.isOpen())
    {
        int col=rand()%5;
        TScore.setString("Score: "+to_string(Score));
        float delay=0.8;
        float time=clocker.getElapsedTime().asSeconds();
        clocker.restart();
        timer+=time;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type==Event::Closed)
            {
                window.close();
            }
            if (event.type==Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case Keyboard::Right:
                        dx=1;
                        break;
                    case Keyboard::Left:
                        dx=-1;
                        break;
                    case Keyboard::Up:
                        rotate=true;
                        break;
                    case Keyboard::Down:
                    delay=0.01;
                    break;
                        
                }
            }
        }
        if (pn){
        for (int i=0; i<4; ++i)
        {
            int x=Tetriminos[nCurrentPiece][i]%2;
            int y=Tetriminos[nCurrentPiece][i]/2;
            //std::cout <<x<<endl;

            CPiece[i].x=x;
            CPiece[i].y=(y-2);
        }
        pn=false;
        }
/////////////////////////////////////MOVE///////////////////////////////////////
if (dx !=0) {
for (int i=0;i<4; ++i )
{
    BPiece[i]=CPiece[i];
    CPiece[i].x+=dx;
}
if (!check()) {
    for (int i=0;i <4;++i)
    {
        CPiece[i]=BPiece[i];
    }
}

dx=0;
}
//////////////////////////////////////////////////////////////////////////////////////
//=============ROTATE=================================================
if (rotate && nCurrentPiece !=4)
{
    Point CP=CPiece[1];
    for (int i=0; i<4;++i)
    {
        BPiece[i]=CPiece[i];
      int x=CP.y-CPiece[i].y;
      int y=CP.x-CPiece[i].x;
      CPiece[i].x=CP.x+x;
      CPiece[i].y=CP.y-y;   
    }
    if (!check())
    {
        for (int i=0; i<4;++i)
        {
            CPiece[i]=BPiece[i];
        }
    }   
    rotate=false;
}
if (timer>delay)
{
    for (int i=0; i<4;++i)
    {
        BPiece[i]=CPiece[i];
        CPiece[i].y+=1;
        //cout <<CPiece[i].y<<endl;
    }
    if (!check()) {
        for (int i=0; i<4; ++i)
        {
            CPiece[i]=BPiece[i];
            Field[BPiece[i].y][BPiece[i].x]=(col+1);
            nCurrentPiece=rand()%7;
        }
        pn=true;
        checklines=true;
    }


    timer=0;
}
///////////////////check for lines////////////////////
if (checklines)
{
    
    for (int py=0;py<FieldHeight;py++)
    {
        int count =0;
        for (int px=0; px<FieldWidth;px++)
        {
            if (Field[py][px]!=0) 
            {
                ++count;
            }
        }
        if (count==FieldWidth)
        {
            Score+=100;
            for (int i=0; i<FieldWidth; i++)
            {
                Field[py][i]=Field[py-1][i];
                Field[py-1][i]=Field[py-2][i];
            }
        }
    }


}


        window.clear(Color(80,80,80,1));
    for (int i=0; i<4; ++i)
    {
        SPiece.setPosition(Vector2f(CPiece[i].x*32,CPiece[i].y*32));
        window.draw(SPiece);
    }
    for (int py=0; py<FieldHeight;++py)
    {
        for (int px=0;px<FieldWidth;++px)
        {
            if (Field[py][px]==0) continue;
            Sprite field;
            field.setTexture(tex[Field[py][px]]);
             SPiece.setTexture(tex[Field[py][px]]);
            field.setPosition(Vector2f(px*32,py*32));

            field.setScale(Vector2f(0.5,0.5));
            window.draw(field);
            TScore.setPosition(Vector2f(320,0));
            window.draw(TScore);
        }
    }
    
    window.display();
    }
    cout <<"game over"<<endl;

}
