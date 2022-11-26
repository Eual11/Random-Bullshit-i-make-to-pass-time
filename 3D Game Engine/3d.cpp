#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
using namespace std;

const int SCREEN_WIDTH = 680;
const int SCREEN_HIGHT = 400;

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
    vector<triangle> tris;
};

struct mat4x4
{
    float m[4][4] = {0};
};

void MultiplyMartrix(vec3d &i,vec3d &o,mat4x4 &multm)
{
    o.x = i.x*multm.m[0][0]+i.y*multm.m[1][0]+i.z*multm.m[2][0]+multm.m[3][0];
    o.y = i.x*multm.m[0][1]+i.y*multm.m[1][1]+i.z*multm.m[2][1]+multm.m[3][1];
    o.z = i.x*multm.m[0][2]+i.y*multm.m[1][2]+i.z*multm.m[2][2]+multm.m[3][2];
    float w = i.x*multm.m[0][3]+i.y*multm.m[1][3]+i.z*multm.m[2][3]+multm.m[3][3];

    if(w !=0.0f)
    {
        o.x/=w;
        o.y/=w;
        o.z/=w;
    }
}
float theta =10;
int main(int argc, char **argv)
{
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

        float zNear = 0.01f;
        float zFar = 100;
        float t = 90;
        float fov = 1.0/(tanf(0.5*t*(3.1415/180)));
        float fAspectRatio = SCREEN_WIDTH/SCREEN_HIGHT;
        float q = zFar/(zFar-zNear);
        mat4x4 matproj;
        matproj.m[0][0]= fAspectRatio*fov;
        matproj.m[1][1] = fov;
        matproj.m[2][2] = q;
        matproj.m[3][2] = -1*zNear*q;
        matproj.m[2][3] = 1;
        matproj.m[3][3] = 0;

        //rotation in to X matrix
        mat4x4 matRotX;
        matRotX.m[0][0] = 1;
        matRotX.m[1][1] = cosf(theta*0.5);
        matRotX.m[1][2] = sinf(theta*0.5);
        matRotX.m[2][1] = -sinf(theta*0.5);
        matRotX.m[2][2] = cosf(theta*0.5);
        matRotX.m[3][3] = 1;

        //rotation in Z matrix;
        mat4x4 matRotZ;
        matRotZ.m[0][0] = cosf(theta*0.5);
        matRotZ.m[0][1] = sinf(theta*0.5);
        matRotZ.m[1][0] = -sinf(theta*0.5);
        matRotZ.m[1][1] = cosf(theta*0.5);
        matRotZ.m[2][2] =1;
        matRotZ.m[3][3] = 1;

        //rendering time lmao

        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;

        if(SDL_Init(SDL_INIT_VIDEO) <0)
        {
            printf("couldn't initialize window %s \n",SDL_GetError());
            return -1;
        }
        window = SDL_CreateWindow("3D go brr?",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HIGHT,SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

        bool close = false;
        SDL_Event e;
        while(!close)
        {
            
            theta+=0.001;
              //rotation in to X matrix
        mat4x4 matRotX;
        matRotX.m[0][0] = 1;
        matRotX.m[1][1] = cosf(theta*0.5);
        matRotX.m[1][2] = sinf(theta*0.5);
        matRotX.m[2][1] = -sinf(theta*0.5);
        matRotX.m[2][2] = cosf(theta*0.5);
        matRotX.m[3][3] = 1;

        //rotation in Z matrix;
        mat4x4 matRotZ;
        matRotZ.m[0][0] = cosf(theta*0.5);
        matRotZ.m[0][1] = sinf(theta*0.5);
        matRotZ.m[1][0] = -sinf(theta*0.5);
        matRotZ.m[1][1] = cosf(theta*0.5);
        matRotZ.m[2][2] =1;
        matRotZ.m[3][3] = 1;
            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_QUIT)
                {
                    close = true;
                }
            }

            for(auto tris: meshCube.tris)
            {
                triangle projectedTriangle;
                triangle rotatedTriangle;
                //rotate the points in to the Z axis

                for(int i =0; i < 3;++i)
                {
                    MultiplyMartrix(tris.p[i],projectedTriangle.p[i],matRotZ);
                }
                 for(int i =0; i < 3;++i)
                {
                    MultiplyMartrix(projectedTriangle.p[i],rotatedTriangle.p[i],matRotX);
                }
                //offset into the screen
                for(int i =0; i < 3; ++i)
                {
                    rotatedTriangle.p[i].z+=3;
                }
                for(int i =0;i <3; i++)
                {
                    MultiplyMartrix(rotatedTriangle.p[i],projectedTriangle.p[i],matproj);
                }
                
                //scaling moment ;__: the pain is practically endless 

                for(int i =0; i <3; i++)
                {
                    projectedTriangle.p[i].x=(projectedTriangle.p[i].x+1)*0.4*SCREEN_WIDTH;
                   projectedTriangle.p[i].y = (projectedTriangle.p[i].y+1)*0.4*SCREEN_HIGHT;

                }
                
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                SDL_RenderDrawLineF(renderer,projectedTriangle.p[0].x,projectedTriangle.p[0].y,projectedTriangle.p[1].x,projectedTriangle.p[1].y);
                SDL_RenderDrawLineF(renderer,projectedTriangle.p[0].x,projectedTriangle.p[0].y,projectedTriangle.p[2].x,projectedTriangle.p[2].y);
                SDL_RenderDrawLineF(renderer,projectedTriangle.p[2].x,projectedTriangle.p[2].y,projectedTriangle.p[1].x,projectedTriangle.p[1].y);
            
            }
            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer,0,0,0,0);
            SDL_RenderClear(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
}