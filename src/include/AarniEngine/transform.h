#ifndef _TRANSFORMH_
#define _TRANSFORMH_

#include <iostream>

#include <AarniEngine/vector.h>
#include <AarniEngine/component.h>

class Transform: public Component
{
    public:
        enum ComponentType componentType = transform;

        Vector3 position = Vector_Zero;
        Vector3 rotation = Vector_Zero;
        Vector3 scale = Vector_One;

        void Reset() override
        {
            ResetPosition();
            ResetRotation();
            ResetScale();
        }

        void ResetPosition()
        {
            position = Vector_Zero;
        }

        void ResetRotation()
        {
            rotation = Vector_Zero;
        }

        void ResetScale()
        {
            scale = Vector_Zero;
        }

        friend std::ostream& operator<<(std::ostream& os, const Transform& pt); //overriding << operator
};

std::ostream& operator<<(std::ostream& os, const Transform& t) // overriding << operator
{
    os << "Position: " << t.position << " Rotation: " << t.rotation << " Scale: " << t.scale;
    return os;
}
#endif