#include <math.h>
#include <vector>
using namespace std;

struct vec3d
{
    float x,y,z;
    float w =1;
};
struct mat4x4
{
    float m[4][4]= {0};
};


vec3d VectorAdd(vec3d &i,vec3d &j)
{
    vec3d v;
    v.x = i.x+j.x;
    v.y = i.y+j.y;
    v.z = i.z+j.z;

    return v;
}
vec3d VectorSubs(vec3d &i, vec3d &j)
{
     vec3d v;
    v.x = i.x-j.x;
    v.y = i.y-j.y;
    v.z = i.z-j.z;
    return v;
}

vec3d VectorMul(vec3d &i, float k)
{
    return {i.x*k, i.y*k,i.z*k};
}
vec3d VectorDiv(vec3d &i, float k)
{
    if(k!=0)
    {
        return {i.x/k, i.y/k, i.z/k};
    }

    return i;
}
float VectorDot(vec3d &i, vec3d &j)
{
    vec3d v;
    v.x = i.x*j.x;
    v.y = i.y * j.y;
    v.z = i.z*j.z;

    return (v.x+v.y+v.z);
}

float VectorLength(vec3d &i)
{
    float l = sqrtf(VectorDot(i,i));
    return l;
}
vec3d VectorNormalize(vec3d &i)
{
    float l = VectorLength(i);
    if(l !=0.0f)
    {
        return {i.x/l,i.y/l,i.z/l};
    }
    return i;
}
vec3d VectorCross(vec3d &i, vec3d &j)
{
    vec3d v;
    v.x = i.y * j.z - i.z * j.y;
    v.y = i.z * j .x - i.x * j.z;
    v.z = i.x * j.y - i.y * j.x;

    return v;
}
mat4x4 MakeProjectionMatrix(float fAspectRatio,float fov,float q,float zNear)
{
    mat4x4 m;
    m.m[0][0] = fAspectRatio*fov;
    m.m[1][1] = fov;
    m.m[2][2] = q;
    m.m[2][3] = 1.0;
    m.m[3][2] = -1 * zNear * q;
    m.m[3][3] = 0;

    return m;
}
mat4x4 MakeRotationMatrixX(float theta)
{
    mat4x4 m;
    theta = theta;
    m.m[0][0] =1.0;
    m.m[1][1] = cosf(theta);
    m.m[1][2] = sin(theta);
    m.m[2][1] = -1*sin(theta);
    m.m[2][2] = cosf(theta);
    m.m[3][3] = 1;

    return m;

}
mat4x4 MakeRotationMatrixZ(float theta)
{
    mat4x4 m;
    theta;
    m.m[0][0] = cosf(theta);
    m.m[0][1] = sinf(theta);
    m.m[1][0] = -1*sinf(theta);
    m.m[1][1] = cosf(theta);
    m.m[2][2] = 1.0;
    m.m[3][3] = 1;

    return m;
 }
 mat4x4 MakeRotationMatrixY(float theta)
 {
    mat4x4 m;
    m.m[0][0] = cosf(theta);
    m.m[0][2] = -1*sinf(theta);
    m.m[1][1] = 1;
    m.m[2][0] = sinf(theta);
    m.m[2][2] = cosf(theta);
    m.m[3][3] = 1;

    return m;
 }
mat4x4 MatrixPointAt(vec3d &pos, vec3d &target, vec3d &up)
{
    vec3d newForward = VectorSubs(target,pos);
    newForward = VectorNormalize(newForward);

    vec3d a = VectorMul(newForward,VectorDot(up,newForward));
    vec3d newUp = VectorSubs(up,a);
    newUp = VectorNormalize(newUp);

    vec3d newRight = VectorCross(newForward,newUp);
    newRight = VectorNormalize(newRight);

    mat4x4 matrix;

    matrix.m[0][0] = newRight.x; matrix.m[0][1] = newRight.y; matrix.m[0][2] = newRight.z; matrix.m[0][3] = 0;
    matrix.m[1][0] = newUp.x; matrix.m[1][1] = newUp.y; matrix.m[1][2] = newUp.z; matrix.m[1][3]= 0;
    matrix.m[2][0] = newForward.x; matrix.m[2][1] = newForward.y; matrix.m[2][2] = newForward.z; matrix.m[2][3] = 0;
    matrix.m[3][0] = pos.x; matrix.m[3][1] = pos.y; matrix.m[3][2] = pos.z; matrix.m[3][3] = 1;

    return matrix;
}
mat4x4 LookatMatrix(mat4x4 &mat)
{
    mat4x4 matrix;
    matrix.m[0][0] = mat.m[0][0]; matrix.m[0][1] = mat.m[1][0];matrix.m[0][2] = mat.m[2][0];matrix.m[0][3] = 0;
    matrix.m[1][0] = mat.m[0][1];matrix.m[1][1] = mat.m[1][1];matrix.m[1][2] = mat.m[2][1];matrix.m[1][3] = 0;
    matrix.m[2][0] = mat.m[0][2];matrix.m[2][1] = mat.m[1][2];matrix.m[2][2] = mat.m[2][2];matrix.m[2][0] = 0;
    matrix.m[3][0] = -(mat.m[3][0] * matrix.m[0][0] + mat.m[3][1] * matrix.m[1][0] + mat.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(mat.m[3][0] * matrix.m[0][1] + mat.m[3][1] * matrix.m[1][1] + mat.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(mat.m[3][0] * matrix.m[0][2] + mat.m[3][1] * matrix.m[1][2] + mat.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
		return matrix;
}