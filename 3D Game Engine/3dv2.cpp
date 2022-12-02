#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include <fstream>
#include <algorithm>
#include <strstream>
#include "include/util.h"
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HIGHT = 480;
struct triangle 
{
    vec3d p[3]; 
    float ln;
};
struct mesh
{
    vector <triangle> tris;


    bool getMesh(std::string filename)
    {
        ifstream  f(filename);
        if(!f.is_open())
        {
            printf("shit not open \n");
            return false;
        }

        vector <vec3d> verts;
        
        
        while(!f.eof())
        {
            char line[256];
            char junk;
            f.getline(line,256);
            strstream s;
            s << line;

            if(line[0] == 'v')
            {
                vec3d v;
                s >> junk >> v.x >> v.y >> v.z;
                //printf("(%d, %d, %d)\n",v.x,v.y,v.z);
                verts.push_back(v);
            }

            if(line[0] == 'f')
            {
                int i[3];
                s >> junk >> i[0]>>i[1]>>i[2];
                tris.push_back({verts[i[0]-1], verts[ i[1] -1 ], verts[i[2] -1 ] });

            }
            
        
        
        
        }
        return true;
    }

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
float thetaY = 0;
float thetaZ =0;
/// @brief 
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

    if(SDL_Init(SDL_INIT_VIDEO) <0)
    {
        printf("couldn't initialize window \n");
        return -1;
    }

    window = SDL_CreateWindow("3Dv2",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HIGHT,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    mesh meshCube;
    meshCube.getMesh("assets/teapot.obj");
    

        float Aspectratio = SCREEN_WIDTH/SCREEN_HIGHT;
        float zFar = 9.0f;
        float zNear = 0.1f;
        float q = zFar/(zFar-zNear);
        float t = 80.0*(3.1415/180);
        float fov = 1.0/(tan(t*0.5));
        vec3d camera = {0,0,0};
        mat4x4 matproj;
        //Projection Matrix
        matproj = MakeProjectionMatrix(Aspectratio,fov,q,zNear);

         //Rotation in X axis
         mat4x4 RotX;
         RotX = MakeRotationMatrixX(theta);
         //Rotaion in the Z axis;

         mat4x4 RotZ;
         RotZ = MakeRotationMatrixZ(theta);
         
         mat4x4 RotY;
        RotY = MakeRotationMatrixY(theta);

    float fYaw =0;
    bool close = false;
    SDL_Event e;
    while(!close)
    {
        //X
         RotX = MakeRotationMatrixX(thetaX);

         //Z
        RotZ = MakeRotationMatrixZ(thetaZ);

        //Y
        RotY = MakeRotationMatrixY(thetaY);

         thetaX+=0.01;
         thetaZ+=0.01;
         vec3d vUp = {0,1,0};
         vec3d vTarget = {0,0,1};
         mat4x4 c = MakeRotationMatrixY(fYaw);
         vec3d look;
        MultiplyMatric(vTarget,look,c);
        vTarget = VectorAdd(camera,look);

        mat4x4 v = MatrixPointAt(camera,vTarget,vUp);
        mat4x4 matview = LookatMatrix(v);


         vector <triangle> projTris; 
        for(auto tris: meshCube.tris)
        {
            triangle projectedTriangle;
            triangle rotatedTriangleX;
            triangle rotatedTriangleXY;
            triangle rotatedTriangleXYZ;
            triangle viewTrig;

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
                rotatedTriangleXYZ.p[i].z+=7;
            }

            vec3d normal,line1,line2;
            line1 = VectorSubs(rotatedTriangleXYZ.p[1],rotatedTriangleXYZ.p[0]);

            
           line2 = VectorSubs(rotatedTriangleXYZ.p[2],rotatedTriangleXYZ.p[0]);
            normal = VectorCross(line1,line2);

            float l = VectorLength(normal);
            normal.x/=l; normal.y/=l; normal.z/=l;
            vec3d rCam = VectorSubs(rotatedTriangleXYZ.p[0],camera);
            float pCam = VectorDot(normal,rCam);
            if( pCam < 0 )
            {
                for(int i=0; i <3; ++i)
                {
                    MultiplyMatric(rotatedTriangleXYZ.p[i],viewTrig.p[i],matview);
                }
                for(int i=0; i < 3; i++)
                {
                    MultiplyMatric(viewTrig.p[i],projectedTriangle.p[i],matproj);
                }
                
                vec3d light_direction = {0,1,1};
                float l = VectorLength(light_direction);
                light_direction.x/=l; light_direction.y/=l;; light_direction.z/=l;

                float ln = fabs(light_direction.x*normal.x + light_direction.y*normal.y+light_direction.z*normal.z) ;
                projectedTriangle.ln = ln;
                vector<SDL_Vertex> verts;
                for(int i=0; i < 3;++i)
                {
                    //projectedTriangle.p[i].x*=-1;
                     projectedTriangle.p[i].y*=-1;
                }
                projTris.push_back(projectedTriangle);
                for(int i =0; i <3; i++)
            {
                SDL_Vertex tv;
                tv.position = {(projectedTriangle.p[i].x+1)*0.5*(double)SCREEN_WIDTH,(double)(1+projectedTriangle.p[i].y)*0.5*(double)SCREEN_HIGHT};
                unsigned char r = i==0? (ln*255):0;
                unsigned char g = i ==1? 255*ln:0;
                unsigned char b = i ==2? 255*ln:0;
                unsigned char a = 255;
                tv.color = {g,r,b,a};
                tv.tex_coord = {0};
                verts.push_back(tv);
            }
        
          }
        }

        //painters algorithm
        sort(projTris.begin(),projTris.end(),[](triangle &t1,triangle &t2)
        {
            float z1 = (t1.p[0].z+t1.p[1].z+t1.p[2].z)/3;
            float z2 = (t2.p[0].z+t2.p[1].z+t2.p[2].z)/3;

            return z1 > z2;
        });

        for (auto tris : projTris)
        {
            vector <SDL_Vertex> verts;
              for(int i =0; i <3; i++)
            {
                SDL_Vertex tv;
                tv.position = {(tris.p[i].x+1)*0.5*(double)SCREEN_WIDTH,(double)(1+tris.p[i].y)*0.5*(double)SCREEN_HIGHT};
                unsigned char r = i==0? (tris.ln*255):0;
                unsigned char g = i ==1? (tris.ln*255):0;
                unsigned char b = i ==2?(tris.ln*255):0;
                unsigned char a = 255;
                tv.color = {r,g,b,a};
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
                        camera.y +=1;
                        break;
                    case SDLK_DOWN:
                          camera.y -=1;
                        break;
                    case SDLK_LEFT:
                        camera.x+=1;
                        break;
                    case SDLK_RIGHT:
                        camera.x-=1;
                        break;
                    case SDLK_w:
                        camera.z+=1;
                        break;
                    case SDLK_s:
                        camera.z-=1;
                        break;
                    case SDLK_a:
                        fYaw-=0.05; //this is fucked up
                        break;
                    case SDLK_d:
                        fYaw+=0.05; // this is fucked up
                        break;
                    
                }
            }
        }

       
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();





}