#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(900,600),"Life",Style::Titlebar|Style::Close);
int main(void)
{
    struct cell {
    int x;
    int y;
    bool alive;
};
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
    vector <cell> vcell;
    window.setFramerateLimit(30);

    for (int i=0; i<2400;++i)
    {
        int x=i%60;
        int y=i/60;
        //cout <<"y: "<<y<< " i "<<i<<endl;
        cell ccell;
        ccell.x=x*15;
        ccell.y=y*15;
        ccell.alive=false;
        vcell.push_back(ccell);
    }
    bool running =false;
    bool input=true;
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
                    //cout <<(x+(y*60))<<endl;
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
                rcell.setPosition(Vector2f(vcell[i].x,vcell[i].y));
                window.draw(rcell);
            }
        }
         //this_thread::sleep_for(50ms);



         if (running && not input)
         {

            for (int i=0; i<vcell.size();i++)
            {
                int ncount=0;
                cell dcell=vcell[i+60];
                
                ncount+=dcell.alive;
                cell rcell=vcell[i+1];
                ncount+=rcell.alive;
                cell drcell=vcell[i+61];
                ncount+=rcell.alive;

                if ((i-1)>=0)
                {
                    if (i>1) {
                    cell lcell=vcell[i-1];
                    ncount+=lcell.alive;
                    }
                    
                    cell dlcell=vcell[i+59];
                    ncount+=dlcell.alive;


                     if (i-60>=0)
                {
                    cell ucell=vcell[i-60];
                    ncount+=ucell.alive;
                    //cout <<vcell[i-60].alive<<" its is i "<<i-60<<endl;;
                    cell urcell=vcell[i-59];
                    ncount+=urcell.alive;
                    if (i>61) {
                    cell ulcell=vcell[i-61];
                    ncount+=ulcell.alive;
                    }
                    
                }
                }
                /////the real shit beigins here/////////////
                if (ncount<2)
                {
                    vcell[i].alive=false;
                    //cout <<i<<endl;
                }
                if (ncount==3 && (not vcell[i].alive))
                {
                    vcell[i].alive=true;
                   // cout <<i<<endl;
                }
                if (ncount>3)
                {
                    vcell[i].alive=false;

                }
               
            }
         }


        window.display();
        }
}