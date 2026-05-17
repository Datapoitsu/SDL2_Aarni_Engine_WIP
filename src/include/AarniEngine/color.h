#ifndef _COLORH_
#define _COLORH_

#include <cstdint>
#include <math.h>
#include <vector>

#include <AarniEngine/curve.h>

struct Color
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;
    public:
    Color(
        int r = 0,
        int g = 0,
        int b = 0, 
        int a = 255):
        r(static_cast<uint8_t>(r)),
        g(static_cast<uint8_t>(g)),
        b(static_cast<uint8_t>(b)),
        a(static_cast<uint8_t>(a)){}; 

    static Color White(){ return {255,255,255,255};}
    static Color Black(){ return {0,0,0,255};}
    static Color Red(){ return {255,0,0,255};}
    static Color Green(){ return {0,255,0,255};}
    static Color Blue(){ return {0,0,255,255};}
    static Color Yellow(){ return {255,255,0,255};}
    static Color Purple(){ return {255,0,255,255};}
    static Color Cyan(){ return {0,255,255,255};}

    static float Average(Color c)
    {
        return (c.r + c.g + c.b) / 3;
    }

    static Color BlackAndWhite(Color c)
    {
        int a = (uint8_t)(Color::Average(c));
        return Color(a,a,a,c.a);
    }

    static int Max(Color c)
    {
        return std::max(std::max(c.r,c.g),c.b);
    }
    
    static int Min(Color c)
    {
        return std::min(std::min(c.r,c.g),c.b);
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const Color& pt); //overriding << operator
};

std::ostream& operator<<(std::ostream& os, const Color& c) // overriding << operator
{
    os << "(" << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ", " << (int)c.a << ")";
    return os;
}

struct ColorGradient
{
    public:
    Curve r,g,b,a;
    ColorGradient(Curve r = Curve::One(), Curve g = Curve::One(), Curve b = Curve::One(), Curve a = Curve::One()): r(r), g(g), b(b), a(a){};
    ColorGradient(Color c): r(Curve::ConstantValue((float)c.r / 255.0f)), g(Curve::ConstantValue((float)c.g / 255.0f)), b(Curve::ConstantValue((float)c.b / 255.0f)), a(Curve::ConstantValue((float)c.a / 255.0f)){};

    Color GetColor(float x)
    {
        return Color(
            (int)(r.GetValue(x) * 255.0f),
            (int)(g.GetValue(x) * 255.0f),
            (int)(b.GetValue(x) * 255.0f),
            (int)(a.GetValue(x) * 255.0f)
        );
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const ColorGradient& pt); //overriding << operator
};

std::ostream& operator<<(std::ostream& os, const ColorGradient& c) // overriding << operator
{
    os << "(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
    return os;
}

#endif