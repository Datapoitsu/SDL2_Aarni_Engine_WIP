#include <math.h>

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