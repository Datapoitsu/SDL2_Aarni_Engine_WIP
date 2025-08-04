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

        void Start()
        {
            componentType = transform;
        }

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

        //Adding transforms.
        Transform& operator+=(const Transform& other)
        {
            position += other.position;
            rotation += other.rotation;
            scale += other.scale;
            return *this;
        }

        friend Transform operator+(Transform t1, const Transform& t2)
        {
            return t1 += t2;
        }

        friend std::ostream& operator<<(std::ostream& os, const Transform& pt); //overriding << operator
};

std::ostream& operator<<(std::ostream& os, const Transform& t) // overriding << operator
{
    os << "Position: " << t.position << " Rotation: " << t.rotation << " Scale: " << t.scale;
    return os;
}
#endif