#ifndef _VECTORH_

#define _VECTORH_
#include <math.h>
#define Vector_Right {1,0,0}
#define Vector_Left {-1,0,0}
#define Vector_Up {0,1,0}
#define Vector_Down {0,-1,0}
#define Vector_Forward {0,0,1}
#define Vector_Back {0,0,-1}
#define Vector_One {1,1,1}
#define Vector_Zero {0,0,0}

struct Vector{
    float x, y, z = 0;
};

void normalize(struct Vector *v)
{
    if(v->x != 0 || v->y != 0 || v->z != 0)
    {
        float magnitude = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
        v->x = v->x / magnitude;
        v->y = v->y / magnitude;
        v->z = v->z / magnitude;
    }
}

float vectorDistance(Vector *v1, Vector *v2){
    return (float)(sqrt(pow(v2->x - v1->x,2) + pow(v2->y - v1->y,2) + pow(v2->z - v1->z,2)));
}
#endif