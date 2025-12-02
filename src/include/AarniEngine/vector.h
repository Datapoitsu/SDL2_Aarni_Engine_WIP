#ifndef _VECTORH_
#define _VECTORH_

#include <math.h>
#include <iostream>

struct Vector3{
    float x, y, z = 0;
    Vector3 (float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {};

    public:
    static Vector3 Zero(){ return {0.0f, 0.0f, 0.0f}; } 
    static Vector3 One(){ return {1.0f, 1.0f, 1.0f}; } 
    static Vector3 Right(){ return {1.0f, 0.0f, 0.0f}; } 
    static Vector3 Left(){ return {-0.0f, 0.0f, 0.0f}; } 
    static Vector3 Up(){ return {0.0f, 1.0f, 0.0f}; } 
    static Vector3 Down(){ return {0.0f, -1.0f, 0.0f}; } 
    static Vector3 Forward(){ return {0.0f, 0.0f, 1.0f}; } 
    static Vector3 Backward(){ return {0.0f, 0.0f, -1.0f}; } 
    
    static float Magnitude(Vector3 v) //Distance from the origin.
    {
        return sqrt(MagnitudeSquared(v));
    }

    static float MagnitudeSquared(Vector3 v)
    {
        return DotProduct(v);
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
        return Zero();
    }

    static Vector3 ClampMagnitude(Vector3 v, float maxDistance)
    {
        return ClampMagnitude(v,0,maxDistance);
    }

    static Vector3 ClampMagnitude(Vector3 v, float minDistance, float maxDistance) //Distance limited vector
    {
        float mag = Magnitude(v);
        if (mag < minDistance)
        {
            return Normalize(v) * minDistance;
        }
        if(mag > maxDistance)
        {
            return Normalize(v) * maxDistance;
        }
        return v;
    }

    static Vector3 Lerp(Vector3 v1, Vector3 v2, float position) //returns the vector where t = 0 is v1 and t = 1 is v2.
    {
        return v1 + (v2 - v1) * position;
    }

    static float DotProduct(Vector3 v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
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

    static Vector3 CrossProduct(Vector3 v1, Vector3 v2)
    {
        return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
    }

    static float Angle(Vector3 v1, Vector3 v2)
    {
        return acosf(DotProduct(v1,v2) / (Magnitude(v1) * Magnitude(v2)));
    }

    static Vector3 Project(Vector3 v1, Vector3 v2)
    {
        return v2 * (DotProduct(v1,v2) / MagnitudeSquared(v2));
    }

    static Vector3 ProjectOnPlane(Vector3 v1, Vector3 v2)
    {
        return v1 - (DotProduct(v1,v2) / MagnitudeSquared(v2)) * v2;
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
    
    static Vector3 Max(Vector3 v1, Vector3 v2) //Returns the greatest value of xyz.
    {
        return {std::max(v1.x,v2.x), std::max(v1.y,v2.y), std::max(v1.z,v2.z)};
    }

    static Vector3 Min(Vector3 v1, Vector3 v2) //Returns the smallest value of xyz.
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
    friend Vector3 operator*(const float f, Vector3 v1);

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
    friend Vector3 operator/(const float f, Vector3 v1);

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

    // ----- Equal ----- //
    bool operator!=(const Vector3& other) const{
        return x != other.x || y != other.y || z != other.z;
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const Vector3& pt); //overriding << operator
};

std::ostream &operator<<(std::ostream &os, const Vector3 &v) // overriding << operator
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

Vector3 operator*(const float f, Vector3 v1)
{
    return {v1.x * f, v1.y * f, v1.z * f};
}

Vector3 operator/(const float f, Vector3 v1)
{
    return {v1.x / f, v1.y / f, v1.z / f};
}

struct Vector2{
    float x, y = 0;
    Vector2 (float x = 0, float y = 0) : x(x), y(y) {};

    public:
    static Vector2 Zero(){ return {0.0f, 0.0f}; } 
    static Vector2 One(){ return {1.0f, 1.0f}; } 
    static Vector2 Right(){ return {1.0f, 0.0f}; } 
    static Vector2 Left(){ return {-1.0f, 0.0f}; } 
    static Vector2 Up(){ return {0.0f, 1.0f}; } 
    static Vector2 Down(){ return {0.0f, -1.0f}; } 

    static float Magnitude(Vector2 v) //Distance from the origin.
    {
        return sqrt(MagnitudeSquared(v));
    }

    static float MagnitudeSquared(Vector2 v)
    {
        return DotProduct(v);
    }

    static float Distance(Vector2 v1, Vector2 v2)
    {
        return Magnitude(v2 - v1);
    }

    static float DistanceSquared(Vector2 v1, Vector2 v2)
    {
        return MagnitudeSquared(v2 - v1);
    }

    static Vector2 Normalize(Vector2 v) //Direction, magnitude = 1
    {
        if(v.x != 0 || v.y != 0)
        {
            return v / Magnitude(v);
        }
        return {0,0};
    }

    static Vector2 ClampMagnitude(Vector2 v, float maxDistance)
    {
        return ClampMagnitude(v,0,maxDistance);
    }

    static Vector2 ClampMagnitude(Vector2 v, float minDistance, float maxDistance) //Distance limited vector
    {
        float mag = Magnitude(v);
        if (mag < minDistance)
        {
            return Normalize(v) * minDistance;
        }
        if(mag > maxDistance)
        {
            return Normalize(v) * maxDistance;
        }
        return v;
    }

    static Vector2 Lerp(Vector2 v1, Vector2 v2, float position) //returns the vector where t = 0 is v1 and t = 1 is v2.
    {
        return v1 + (v2 - v1) * position;
    }

    static float DotProduct(Vector2 v)
    {
        return v.x * v.x + v.y * v.y;
    }

    static float DotProduct(Vector2 v1, Vector2 v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    static Vector2 MoveTowards(Vector2 start, Vector2 end, float distance)
    {
        if (Magnitude(end - start) < distance)
        {
            return end;
        }
        return start + Normalize(end - start) * distance; 
    }

    static Vector2 Reflect(Vector2 direction, Vector2 normal)
    {
        return direction - normal * 2 * DotProduct(direction,normal);
    }

    static float Angle(Vector2 v1, Vector2 v2)
    {
        return acosf(DotProduct(v1,v2) / (Magnitude(v1) * Magnitude(v2)));
    }

    static Vector2 Abs(Vector2 v)
    {
        return {abs(v.x),abs(v.y)};
    }

    static Vector2 Ceil(Vector2 v)
    {
        return {ceil(v.x),ceil(v.y)};
    }
    
    static Vector2 Floor(Vector2 v)
    {
        return {floor(v.x),floor(v.y)};
    }

    static Vector2 Round(Vector2 v)
    {
        return {round(v.x),round(v.y)};
    }

    static Vector2 Sign(Vector2 v)
    {
        return {v.x == 0.0f ? 0.0f : v.x > 0.0f ? 1.0f : -1.0f, v.y == 0.0f ? 0.0f : v.y > 0.0f ? 1.0f : -1.0f};
    }
    
    static Vector2 Max(Vector2 v1, Vector2 v2) //Returns the greatest value of xyz.
    {
        return {std::max(v1.x,v2.x), std::max(v1.y,v2.y)};
    }

    static Vector2 Min(Vector2 v1, Vector2 v2) //Returns the smallest value of xyz.
    {
        return {std::min(v1.x,v2.x), std::min(v1.y,v2.y)};
    }

    static float MannhattanDistance(Vector2 v)
    {
        return abs(v.x) + abs(v.y);
    }

    static float MannhattanDistance(Vector2 v1, Vector2 v2)
    {
        return MannhattanDistance(v2 - v1);
    }

    // -------------------- Overriding operators -------------------- //

    // ----- plus ----- //
    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    friend Vector2 operator+(Vector2 v1, const Vector2& v2)
    {
        return v1 += v2;
    }

    Vector2 operator+() const{
        return Vector2(x, y);
    }

    // ----- Minus ----- //
    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    friend Vector2 operator-(Vector2 v1, const Vector2& v2)
    {
        return v1 -= v2;
    }

    Vector2 operator-() const{
        return Vector2(-x, -y);
    }

    // ----- Multiplication ----- //
    friend Vector2 operator*(Vector2 v1, const float f)
    {
        return {v1.x * f, v1.y * f};
    }
    friend Vector2 operator*(const float f, Vector2 v1);
    Vector2& operator*=(const float& multiplier)
    {
        x *= multiplier;
        y *= multiplier;
        return *this;
    }

    // ----- Division ----- //
    friend Vector2 operator/(Vector2 v1, const float f)
    {
        return {v1.x / f, v1.y / f};
    }
    friend Vector2 operator/(const float f, Vector2 v1);
    Vector2& operator/=(const float& multiplier)
    {
        x /= multiplier;
        y /= multiplier;
        return *this;
    }

    // ----- Equal ----- //
    bool operator==(const Vector2& other) const{
        return x == other.x && y == other.y;
    }

    // ----- Not equal ----- //
    bool operator!=(const Vector2& other) const{
        return x != other.x || y != other.y;
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const Vector3& pt); //overriding << operator
};

std::ostream& operator<<(std::ostream& os, const Vector2& v) // overriding << operator
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

Vector2 operator*(const float f, Vector2 v1)
{
    return {v1.x * f, v1.y * f};
}

Vector2 operator/(const float f, Vector2 v1)
{
    return {v1.x / f, v1.y / f};
}

#endif