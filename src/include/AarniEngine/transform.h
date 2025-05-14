#ifndef _TRANSFORMH_
#define _TRANSFORMH_

#include <AarniEngine/vector.h>
#include <AarniEngine/component.h>

#define Transform_Empty {Vector_Zero,Vector_Zero,Vector_Zero}

class Transform: public Component
{
    public:
        Vector3 position = Vector_Zero;
        Vector3 rotation = Vector_Zero;
        Vector3 scale = Vector_Zero;

        void Reset() override
        {
            position = Vector_Zero;
            rotation = Vector_Zero;
            scale = Vector_Zero;
        }

        void PrintData()
        {
            std::cout << position.x << position.y << position.z << std::endl;
        }
};
#endif