#ifndef _TRANSFORMH_
#define _TRANSFORMH_

#include <iostream>

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

        friend std::ostream& operator<<(std::ostream& os, const Transform& pt); //overriding << operator
};

std::ostream& operator<<(std::ostream& os, const Transform& t) // overriding << operator
{
    os << "Position: " << t.position << " Rotation: " << t.rotation << " Scale: " << t.scale;
    return os;
}
#endif