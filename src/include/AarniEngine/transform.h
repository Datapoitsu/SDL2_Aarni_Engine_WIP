#ifndef _TRANSFORMH_
#define _TRANSFORMH_

#include <AarniEngine/vector.h>

struct Transform
{
    Vector position;
    Vector rotation;
    Vector scale;
};

void ResetObject(Transform *O){
    O->position = Vector_Zero;
    O->rotation = Vector_Zero;
    O->scale = Vector_Zero;
}

#endif