#ifndef _TRANSFORMH_
#define _TRANSFORMH_

#include <AarniEngine/vector.h>

#define Transform_Empty {Vector_Zero,Vector_Zero,Vector_Zero}

struct Transform
{
    Vector3 position = Vector_Zero;
    Vector3 rotation = Vector_Zero;
    Vector3 scale = Vector_Zero;
};

void ResetObject(Transform *O){
    *O = Transform_Empty;
}

#endif