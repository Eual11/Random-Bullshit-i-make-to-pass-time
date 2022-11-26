#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HIGHT = 480;

struct vec3d
{
    float x,y,z;
};

struct triangle 
{
    vec3d p[3]; 
};
struct mesh
{
    vector <triangle> tris;
};

struct mat4x4
{
    float m[4][4]= {0};
};

void MultiplyMatric(vec3d &i, vec3d &o,mat4x4 &mat)
{
    o.x = i.x * mat.m[0][0]+i.y*mat.m[1][0]+i.z*mat.m[2][0]+mat.m[3][0];
    o.y = i.x * mat.m[0][1]+i.y*mat.m[1][1]+i.z*mat.m[2][1]+mat.m[3][1];
    o.z = i.x * mat.m[0][2]+i.y*mat.m[1][2]+i.z*mat.m[2][2]+mat.m[3][2];
    float w = i.x * mat.m[0][3]+i.y*mat.m[1][3]+i.z*mat.m[2][3]+mat.m[3][3];

    if(w !=0.0f)
    {
        o.x/=w;
        o.y/=w;
        o.z/=w;
    }

}
float theta =0;
float thetaX =0;
float thetaY = -0.5;
float thetaZ =0;
int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) <0)
    {
        printf("couldn't initialize window \n");
        return -1;
    }

    window = SDL_CreateWindow("3Dv2",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HIGHT,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    mesh meshCube;
    meshCube.tris = {

		// SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		};
        float Aspectratio = SCREEN_WIDTH/SCREEN_HIGHT;
        float zFar = 9.0f;
        float zNear = 0.1f;
        float q = zFar/(zFar-zNear);
        float t = 80.0*(3.1415/180);
        float fov = 1.0/(tan(t*0.5));
         
         mat4x4 matproj;
         matproj.m[0][0] = Aspectratio*fov;
         matproj.m[1][1] = fov;
         matproj.m[2][2] = q;
         matproj.m[2][3] = 1;
         matproj.m[3][2] = -1*zNear*q;
         matproj.m[3][3] = 0;

         //Rotation in X axis
         mat4x4 RotX;
         RotX.m[0][0] = 1;
         RotX.m[1][1] = cosf(0.5*theta);
         RotX.m[1][2] = sinf(0.5*theta);
         RotX.m[2][1] = -sinf(0.5*theta);
         RotX.m[2][2] = cosf(0.5*theta);
         RotX.m[3][3] = 1.0;

         //Rotaion in the Z axis;

         mat4x4 RotZ;
         RotZ.m[0][0] = cosf(0.5*theta);
         RotZ.m[0][1] = sinf(theta*0.5);
         RotZ.m[1][0] = -sinf(0.5*theta);
         RotZ.m[1][1] = cosf(theta*0.5);
         RotZ.m[2][2] = 1.0;
         RotZ.m[3][3] = 1.0;
         
         mat4x4 RotY;
         RotY.m[0][0] = cosf(theta *0.5);
         RotY.m[0][2] = -sinf(theta*0.5);
         RotY.m[1][1] = 1.0;
         RotY.m[2][0] = sinf(theta*0.5);
         RotY.m[2][2] = cosf(theta*0.5);
         RotY.m[3][3] = 1.0; 

    
    bool close = false;
    SDL_Event e;
    while(!close)
    {
        //X
         RotX.m[0][0] = 1;
         RotX.m[1][1] = cosf(0.5*thetaX);
         RotX.m[1][2] = sinf(0.5*thetaX);
         RotX.m[2][1] = -sinf(0.5*thetaX);
         RotX.m[2][2] = cosf(0.5*thetaX);
         RotX.m[3][3] = 1.0;

         //Z
         RotZ.m[0][0] = cosf(0.5*thetaZ);
         RotZ.m[0][1] = sinf(thetaZ*0.5);
         RotZ.m[1][0] = -sinf(0.5*thetaZ);
         RotZ.m[1][1] = cosf(thetaZ*0.5);
         RotZ.m[2][2] = 1.0;
         RotZ.m[3][3] = 1.0;

        //Y
         RotY.m[0][0] = cosf(thetaY *0.5);
         RotY.m[0][2] = -sinf(thetaY*0.5);
         RotY.m[1][1] = 1.0;
         RotY.m[2][0] = sinf(thetaY*0.5);
         RotY.m[2][2] = cosf(thetaY*0.5);
         RotY.m[3][3] = 1.0; 


         //thetaX+=0.1;
        for(auto tris: meshCube.tris)
        {
            triangle projectedTriangle;
            triangle rotatedTriangleX;
            triangle rotatedTriangleXY;
            triangle rotatedTriangleXYZ;

            for(int i =0; i <3; ++i)
            {//rotate to X axis
                MultiplyMatric(tris.p[i],rotatedTriangleX.p[i],RotX);
            }
            for(int i =0; i <3;i++)
            {
                //Y
                MultiplyMatric(rotatedTriangleX.p[i],rotatedTriangleXY.p[i],RotY);
            }
            for(int i =0; i < 3; ++i)
            {
                //rotate into z axis
                MultiplyMatric(rotatedTriangleXY.p[i],rotatedTriangleXYZ.p[i],RotZ);
            }


            for(int i =0; i <3; ++i)
            {
                rotatedTriangleXYZ.p[i].z+=3;
            }
            for(int i=0; i < 3; i++)
            {
                MultiplyMatric(rotatedTriangleXYZ.p[i],projectedTriangle.p[i],matproj);
            }
            

        vector<SDL_Vertex> verts;
        for(int i =0; i <3; i++)
        {
            SDL_Vertex tv;
            tv.position = {(projectedTriangle.p[i].x+1)*0.5*(double)SCREEN_WIDTH,(double)(1+projectedTriangle.p[i].y)*0.5*(double)SCREEN_HIGHT};
            unsigned char r = i ==0? 255:0;
            unsigned char g = i ==1? 255:0;
            unsigned char b = i ==2? 255:0;
            unsigned char a = 255;
            tv.color = {255,r,r,a};
            tv.tex_coord = {0};
            verts.push_back(tv);
        }
        

        SDL_RenderGeometry(renderer,nullptr,verts.data(),verts.size(),nullptr,0);
       
        }

         SDL_RenderPresent(renderer);
         SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                close = true;
            }

            if(e.type = SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                        thetaX+=1;
                        break;
                    case SDLK_DOWN:
                        thetaX-=1;
                        break;
                    case SDLK_LEFT:
                        thetaY+=1;
                        break;
                    case SDLK_RIGHT:
                        thetaY-=1;
                        break;
                }
            }
        }

       
        

        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();





}