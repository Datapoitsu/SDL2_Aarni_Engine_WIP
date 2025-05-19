#ifndef _VECTORH_
#define _VECTORH_

/*
TODO:
    Cross()
    Project()
    ProjectOnPlane()
    RotateTowards()
*/

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
    static float Magnitude(Vector3 v) //Distance from the origin.
    {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    static float MagnitudeSquared(Vector3 v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    static float Distance(Vector3 v1, Vector3 v2)
    {
        return Magnitude(v2 - v1);
    }

    static float DistanceSquared(Vector3 v1, Vector3 v2)
    {
        return MagnitudeSquared(v2 - v1);
    }

    static Vector3 Normalize(Vector3 v) //Direction, magnitude = 1
    {
        if(v.x != 0 || v.y != 0 || v.z != 0)
        {
            return v / Magnitude(v);
        }
        return Vector_Zero;
    }

    static Vector3 ClampMagnitude(Vector3 v1, float maxDistance)
    {
        return ClampMagnitude(v1,0,maxDistance);
    }

    static Vector3 ClampMagnitude(Vector3 v1, float minDistance, float maxDistance) //Distance limited vector
    {
        if (Magnitude(v1) < minDistance)
        {
            return Normalize(v1) * minDistance;
        }
        if(Magnitude(v1) > maxDistance)
        {
            return Normalize(v1) * maxDistance;
        }
        return v1;
    }

    static float Angle(Vector3 v1, Vector3 v2)
    {
        float aSquared = MagnitudeSquared(v1);
        float bSquared = MagnitudeSquared(v2);
        float cSquared = DistanceSquared(v1,v2);
        float a = sqrt(aSquared);
        float b = sqrt(bSquared);
        float c = sqrt(cSquared);
        std::cout << aSquared << "; " << bSquared << "; " << cSquared << std::endl;
        std::cout << a << "; " << b << "; " << c << std::endl;
        return acosf((aSquared + bSquared - cSquared) / (2 * sqrt(aSquared) * sqrt(bSquared))) * 180 / 3.14159;
    }

    static Vector3 Lerp(Vector3 v1, Vector3 v2, float position) //returns the vector where t = 0 is v1 and t = 1 is v2.
    {
        return v1 + (v2 - v1) * position;
    }

    static float DotProduct(Vector3 v1, Vector3 v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    static Vector3 MoveTowards(Vector3 start, Vector3 end, float distance)
    {
        if (Magnitude(end - start) < distance)
        {
            return end;
        }
        return start + Normalize(end - start) * distance; 
    }

    static Vector3 Reflect(Vector3 direction, Vector3 normal)
    {
        return direction - normal * 2 * DotProduct(direction,normal);
    }

    static Vector3 Abs(Vector3 v)
    {
        return {abs(v.x),abs(v.y),abs(v.z)};
    }

    static Vector3 Ceil(Vector3 v)
    {
        return {ceil(v.x),ceil(v.y),ceil(v.z)};
    }
    
    static Vector3 Floor(Vector3 v)
    {
        return {floor(v.x),floor(v.y),floor(v.z)};
    }

    static Vector3 Round(Vector3 v)
    {
        return {round(v.x),round(v.y),round(v.z)};
    }

    static Vector3 Sign(Vector3 v)
    {
        return {v.x == 0.0f ? 0.0f : v.x > 0.0f ? 1.0f : -1.0f, v.y == 0.0f ? 0.0f : v.y > 0.0f ? 1.0f : -1.0f, v.z == 0.0f ? 0.0f : v.z > 0.0f ? 1.0f : -1.0f};
    }
    
    static Vector3 Max(Vector3 v1, Vector3 v2)
    {
        return {std::max(v1.x,v2.x), std::max(v1.y,v2.y), std::max(v1.z,v2.z)};
    }

    static Vector3 Min(Vector3 v1, Vector3 v2)
    {
        return {std::min(v1.x,v2.x), std::min(v1.y,v2.y), std::min(v1.z,v2.z)};
    }

    static float MannhattanDistance(Vector3 v)
    {
        return abs(v.x) + abs(v.y) + abs(v.z);
    }

    static float MannhattanDistance(Vector3 v1, Vector3 v2)
    {
        return MannhattanDistance(v2 - v1);
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

    // ----- Equal ----- //
    bool operator==(const Vector3& other) const{
        return x == other.x && y == other.y && z == other.z;
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const Vector3& pt); //overriding << operator
};

std::ostream& operator<<(std::ostream& os, const Vector3& v1) // overriding << operator
{
    os << "(" << v1.x << ", " << v1.y << ", " << v1.z << ")";
    return os;
}

void TestVector()
{
    Vector3 v1 = {2,0,0};
    Vector3 v2 = {4,4,0};
    std::cout << Vector3::Angle(v1,v2) << std::endl;
}

#endif