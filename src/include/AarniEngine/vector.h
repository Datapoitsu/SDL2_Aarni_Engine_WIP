#ifndef _VECTORH_
#define _VECTORH_

#include <math.h>
#include <iostream>
#define Vector_Right {1,0,0}
#define Vector_Left {-1,0,0}
#define Vector_Up {0,1,0}
#define Vector_Down {0,-1,0}
#define Vector_Forward {0,0,1}
#define Vector_Back {0,0,-1}
#define Vector_One {1,1,1}
#define Vector_Zero {0,0,0}

struct Vector3{
    float x, y, z = 0;
    Vector3 (float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {};

    public:
    static float Magnitude(Vector3 v) //Calculates the hypotenus of the vector aka. distance
    {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    static float Distance(Vector3 v1, Vector3 v2)
    {
        return Magnitude(v2 - v1);
    }

    static Vector3 Normalized(Vector3 v)
    {
        if(v.x != 0 || v.y != 0 || v.z != 0)
        {
            return v / Magnitude(v);
        }
        return Vector_Zero;
    }

    static float Angle(Vector3 v1, Vector3 v2)
    {
        return asin(Distance(v1,v2) / Magnitude(v2));
    }

    static Vector3 Lerp(Vector3 v1, Vector3 v2, float t) //returns the vector where t = 0 is v1 and t = 1 is v2.
    {
        return v1 + (v2 - v1) * t;
    }

    // -------------------- Overriding operators -------------------- //
    // ----- plus ----- //
    Vector3& operator+=(const Vector3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    friend Vector3 operator+(Vector3 v1, const Vector3& v2)
    {
        return v1 += v2;
    }

    Vector3 operator+() const{
        return Vector3(x, y, z);
    }

    // ----- Minus ----- //
    Vector3& operator-=(const Vector3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    friend Vector3 operator-(Vector3 v1, const Vector3& v2)
    {
        return v1 -= v2;
    }

    Vector3 operator-() const{
        return Vector3(-x, -y, -z);
    }

    // ----- Multiplication ----- //
    friend Vector3 operator*(Vector3 v1, const float f)
    {
        return {v1.x * f, v1.y * f, v1.z * f};
    }

    Vector3& operator*=(const float& multiplier)
    {
        x *= multiplier;
        y *= multiplier;
        z *= multiplier;
        return *this;
    }

    // ----- Division ----- //
    friend Vector3 operator/(Vector3 v1, const float f)
    {
        return {v1.x / f, v1.y / f, v1.z / f};
    }

    Vector3& operator/=(const float& multiplier)
    {
        x /= multiplier;
        y /= multiplier;
        z /= multiplier;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& pt); //overriding << operator
};

std::ostream& operator<<(std::ostream& os, const Vector3& v1) // overriding << operator
{
    os << "(" << v1.x << ", " << v1.y << ", " << v1.z << ")";
    return os;
}

void StartVectorTest()
{
    Vector3 v1 = {1,1,0};
    Vector3 v2 = {1,1,1};
    std::cout << Vector3::Angle(v1,v2) << std::endl;
}
#endif