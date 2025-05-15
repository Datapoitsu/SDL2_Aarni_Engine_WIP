#ifndef _TRANSFORMH_
#define _TRANSFORMH_

#include <AarniEngine/vector.h>
#include <AarniEngine/component.h>

class Transform: public Component
{
    public:
        Vector3 position = Vector_Zero;
        Vector3 rotation = Vector_Zero;
        Vector3 scale = Vector_One;

        void Reset() override
        {
            position = Vector_Zero;
            rotation = Vector_Zero;
            scale = Vector_One;
        }

        void PrintData()
        {
            std::cout << "Position X:" << position.x << " Y:" << position.y << " Z:" << position.z << std::endl;
            std::cout << "Rotation X:" << rotation.x << " Y:" << rotation.y << " Z:" << rotation.z << std::endl;
            std::cout << "Scale X:" << scale.x << " Y:" << scale.y << " Z:" << scale.z << std::endl;
        }
};
#endif