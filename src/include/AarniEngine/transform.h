#ifndef _TRANSFORMH_
#define _TRANSFORMH_

#include <iostream>

#include <AarniEngine/vector.h>
#include <AarniEngine/component.h>
#include <AarniEngine/quaternion.h>

class Transform: public Component
{
    public:
        Vector3 position = Vector3::Zero();
        Quaternion rotation = Quaternion::Zero();
        Vector3 scale = Vector3::Zero();

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
            position = Vector3::Zero();
        }

        void ResetRotation()
        {
            rotation = Quaternion::Zero();
        }

        void ResetScale()
        {
            scale = Vector3::Zero();
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