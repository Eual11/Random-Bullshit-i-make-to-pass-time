#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;
using namespace sf;


float slope(float x1,float y1,float x2,float y2);
RenderWindow window(VideoMode(800,600),"koch's curve",Style::Close);

struct point
{
    float x;
    float y;
    int n =0;

};
float pi = 2*acos(0.0);
bool render = false;
int main(void)
{
    window.setFramerateLimit(60);

    vector <point> Vcurve; //the vector representation of the coordinates
    VertexArray curve; //the curve to be rendered

    vector <point> tmp;// a template vector for points transition
    Vertex p1,p2,p3; //the first 3 points that represent the triangle or level 0
    p1.position = Vector2f(400,200);
    p2.position = Vector2f(278.5,443);
    p3.position = Vector2f(521.5,443);
///**the triangle, level zero
    curve.append(p1);
    curve.append(p3);
    curve.append(p2);
    curve.append(p1);
/////////////////////////////////
for (int i = 0; i <4; ++i)
{
    point p;
    p.x = curve[i].position.x;
    p.y = curve[i].position.y;
    Vcurve.push_back(p);
}

int j =0;
curve.clear();
 
 /*
 for (int i =0; i <Vcurve.size(); ++i)
 {
    Vertex p1;
    p1.position.x = Vcurve[i].x;
   p1.position.y = Vcurve[i].y;
   if (Vcurve[i].n == 1)
   {
    p1.color = Color::Red;
   }
   else if (Vcurve[i].n == 2)
   {
    p1.color = Color::Magenta;
   }
   curve.append(p1);
 }
*/
for (auto d : Vcurve)
{
   // cout<<"("<<d.x<<","<<d.y<<")"<<endl;
}

    while (window.isOpen())
    {
        Event event;

        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.key.code == Keyboard::E  && event.type == Event::KeyPressed)
            {
                render = true;
            }
        }

        if (render)
        {
            render = false;
            tmp.clear();

            //////////////////////================================================================================================/////////////////////////

            
for (int i =0; i <Vcurve.size(); ++i)
{
    if (i < Vcurve.size()-1)
    {
        point curPoint=Vcurve[i] ;
        point nexPoint = Vcurve[i+1];

        float delX = (nexPoint.x - curPoint.x) / 3; //the change in position to divide the interval with 3 equal points
       
        float delY = (nexPoint.y - curPoint.y) /3 ; //the change in position
        float delG = fabs(delX)>0? fabs(delX):fabs(delY);
        point newPoint1;
        point newPoint2;
        point cenPoint;
        newPoint1.x = curPoint.x + delX;
        newPoint1.y = curPoint.y + delY;
        newPoint1.n =1;
        newPoint2.n=1;

        newPoint2.x = curPoint.x + (2*delX);
        newPoint2.y = curPoint.y + (2*delY);
        float dist = ((newPoint1.x - newPoint2.x)*(newPoint1.x - newPoint2.x)) + ((newPoint1.y - newPoint2.y)*(newPoint1.y - newPoint2.y));
        dist = (sqrt(dist));
        cenPoint.x = (newPoint1.x+newPoint2.x)/2;
        cenPoint.y = (newPoint1.y + newPoint2.y)/2;
        if (!slope(newPoint1.x,newPoint1.y,newPoint2.x,newPoint2.y) )
        {
            cenPoint.y -=delX;

            
        }
        else if(slope(newPoint1.x,newPoint1.y,newPoint2.x,newPoint2.y) >0)
        {
            cenPoint.y-=delY/2;
            cenPoint.x+=delY;
            
        }
        else 
        {
            cenPoint.y-=delX;
            cenPoint.x-=2*delX;
            
        }

        cenPoint.n = 2;

        tmp.push_back(Vcurve[i]);
        tmp.push_back(newPoint1);
        tmp.push_back(cenPoint);
        tmp.push_back(newPoint2);
        

    }

    else 
    {
        tmp.push_back(Vcurve[i]);
    }
   
    
}


            //==================================================================================================================




            swap(tmp,Vcurve);
            
        }

       for (int i =0; i <Vcurve.size()-1; ++i)
       {
        Vertex p1;
        p1.position = Vector2f(Vcurve[i].x,Vcurve[i].y);
        //cout <<p1.position.x<<" , "<<p1.position.y<<endl;
        Vertex p2;
        p2.position = Vector2f(Vcurve[i+1].x, Vcurve[i+1].y);
        //cout <<p2.position.x<<" , "<<p2.position.y<<endl;

        VertexArray line(Lines,2);
        line.append(p1);
        line.append(p2);
        window.draw(line);

       }
       
        window.display();
        window.clear();
    }
    
    


}

float slope(float x1,float y1,float x2,float y2)
{
    return (y2-y1)/(x2-x1);
}