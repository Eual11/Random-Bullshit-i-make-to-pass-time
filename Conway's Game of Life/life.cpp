#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
using namespace std;
using namespace sf;
//a window with a static window size of 900x600
RenderWindow window(VideoMode(900,600),"Life",Style::Titlebar|Style::Close);
int main(void)
{
    struct cell {
    int x;
    int y;
    bool alive;
    int live;
};
///Vertex array for somehow not visible horizontal grids lines ///
    VertexArray GridX(Lines,80);
    //settings.antialiasingLevel=10;
    for (int i=0; i<80;++i)
    {
        Vertex verti;
        verti.color=Color(255,255,255,1);
        verti.position=Vector2f(0,(15*i));
        GridX.append(verti);
        verti.position=Vector2f(1000,(15*i));
        GridX.append(verti);
    }

    ///vertex array for somehow invisible vertical grid lines
    VertexArray GridY(Lines,180);
    for (int i=0; i<180;++i)
    {
        Vertex verti;
        verti.color=Color(255,255,255,1);
        verti.position=Vector2f(15*i,0);
        GridY.append(verti);
        verti.position=Vector2f(15*i,1000);
        GridY.append(verti);
    }
    ///initialising a vector (dynamic array) of cells///
    vector <cell> vcell;
    window.setFramerateLimit(30);

    for (int i=0; i<2400;++i)
    {
        int x=i%60;
        int y=i/60;
        cell ccell;
        ccell.x=x*15;
        ccell.y=y*15;
        ccell.alive=false;
        vcell.push_back(ccell);
    }
    bool running =false;
    bool input=true;
    window.setFramerateLimit(35);
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
      
        {
            if (event.type==Event::Closed)
            {
                window.close();
            }
            if (event.type==Event::MouseButtonPressed && input)
            {
                switch (event.key.code)
                {
                    case Mouse::Left:
                    //cout <<"left button"<<endl;
                    int x=Mouse::getPosition(window).x/15;
                    int y=Mouse::getPosition(window).y/15;
                    //cout <<Mouse::getPosition(window).x<< " , "<<Mouse::getPosition(window).y<<endl;
                    //cout <<vcell[(x+(y*60))].live<<endl;
                    vcell[(x+(y*60))].alive= !vcell[(x+(y*60))].alive;
                    break;

                }
            }

            if (event.key.code==Keyboard::E)
            {
                running=true;
                input=false;
            }
            if (event.key.code==Keyboard::B)
            {
                running=false;
                input=true;
            }
        }
        window.draw(GridX);
        window.draw(GridY);
        
        window.clear(); 
        for (int i=0; i<vcell.size(); ++i)
        {
            if (vcell[i].alive)
            {
                 
                RectangleShape rcell;
                rcell.setSize(Vector2f(15,15));
                rcell.setFillColor(Color::Green);
                rcell.setOutlineThickness(0.6);
                rcell.setOutlineColor(Color::White);
                rcell.setPosition(Vector2f(vcell[i].x,vcell[i].y));
                window.draw(rcell);
            }
        }

         if (running && not input)
         {

            for (int i=0; i<vcell.size();i++)
            {
                vcell[i].live=0;
                cell dcell=vcell[i+60];
                vcell[i].live+=dcell.alive;
                cell rcell=vcell[i+1];
                vcell[i].live+=rcell.alive;
                cell drcell=vcell[i+61];
                vcell[i].live+=drcell.alive;

                if ((i-1)>=0)
                {
                    if (i>1) {
                    cell lcell=vcell[i-1];  ///the cell to the left of the given cell vcell[i]
                   
                    vcell[i].live+=lcell.alive;
                    }
                    
                    cell dlcell=vcell[i+59];  //the cell down left of the given cell
                   
                    vcell[i].live+=dlcell.alive;
                    ///incrementing the number of life cells around our cell of interest by the state of the neighbor cell


                     if (i-60>=0)
                {
                    cell ucell=vcell[i-60];
                    vcell[i].live+=ucell.alive;
                    cell urcell=vcell[i-59];
                    vcell[i].live+=urcell.alive;
                    if (i>61) {
                    cell ulcell=vcell[i-61];
                    vcell[i].live+=ulcell.alive;
                    }   
                }
                }  
            }
         for (int i=0; i<vcell.size();++i)
         {
            if (vcell[i].live>3 && vcell[i].alive)
            {
                //rule 3: any live cell with more than 3 live neighbours dies as if by overpopulation
                vcell[i].alive=false;
            }
            if (vcell[i].live<2 && vcell[i].alive)
            {
                //rule 1: any life cell with fewer than two live cells neighbours dies as if by underpopulation
                vcell[i].alive=false;
            }
            if (vcell[i].live==3 && (not vcell[i].alive)){

                //rule 2: dead live cell with exactly 3 live neighbor cells becomes alive
                vcell[i].alive=true;
            }

         }
         
         }
        window.display();
        }
}