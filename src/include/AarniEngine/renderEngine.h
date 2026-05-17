#ifndef _RENDERENGINE_
#define _RENDERENGINE_

#include <SDL2/SDL_image.h>
#include <AarniEngine/component.h>
#include <AarniEngine/ball.h>

//Application variables
SDL_Window *Window;
SDL_Renderer *RenderInformation;
const int screenWidth = 1000;
const int screenHeigth = 1000;
int backgroundColour[3] = {125,125,125};
void DrawBallsRecusive(Component *c, Transform *t);

bool createWindow()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Window = SDL_CreateWindow("SDL Practice",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,screenWidth,screenHeigth,SDL_WINDOW_ALLOW_HIGHDPI);
    if (Window != NULL)
    {
        RenderInformation = SDL_CreateRenderer(Window, -1, 0);
        std::cout << "Did create a window!" << std::endl; 
    }
    else
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }
    return Window != NULL;
}

void closeWindow()
{
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

struct RenderObject
{
    Transform transform; //Calculated value of all transfroms from root to renderer.
    Renderer renderer;
};

void DrawLineSimple(int x1, int y1, int x2, int y2, Color color) //Bresenham's line algorithm
{
    SDL_SetRenderDrawColor(RenderInformation,color.r, color.g, color.b, color.a);
    int dx = x2 - x1;
    int dy = y2 - y1;
    if(abs(dx) >= abs(dy)) //Horizontal draw.
    {
        float m = Vector2Int::Slope({x1,y1},{x2,y2});
        if(x2 < x1) //Swaping oreder of value for loop to function.
        {
            std::swap(x1,x2);
            std::swap(y1,y2);
        }

        for(int x = x1; x < x2 ; x++)
        {
            SDL_RenderDrawPoint(RenderInformation, x, y1 + m * (x - x1));
        }
    }
    else //Vertical draw.
    {
        float m = Vector2Int::Slope({y1,x1},{y2,x2});
        if(y2 < y1) //Swaping oreder of value for loop to function.
        {
            std::swap(x1,x2);
            std::swap(y1,y2);
        }
        
        for(int y = y1; y < y2; y++)
        {
            SDL_RenderDrawPoint(RenderInformation, m*(y-y1) + x1, y);
        }
    }
}

void DrawLineSimple(Vector2Int v1, Vector2Int v2, Color color)
{
    DrawLineSimple(v1.x, v1.y, v2.x, v2.y, color);
}

void DrawLineSimple(Vector2 v1, Vector2 v2, Color color)
{
    DrawLineSimple(static_cast<int>(v1.x), static_cast<int>(v1.y), static_cast<int>(v2.x), static_cast<int>(v2.y), color);
}

void DrawLineAntiAliasing(float x1, float y1, float x2, float y2, Color color)
{
    int steep = abs(y2 - y1) > abs(x2 - x1);
    if(steep) //Swapping horizontal with vectical.
    {
        std::swap(x1,y1);
        std::swap(x2,y2);
    }
    if(x1 > x2) //Swapping first one to be most left one.
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }

    float m = Vector2::Slope({x1,y1},{x2,y2});
    if(x2 - x1 == 0)
    {
        m = 1;
    }
    float intersectY = y1;

    if(steep)
    {
        int x;
        for(x = x1; x <= x2; x++)
        {
            SDL_SetRenderDrawColor(RenderInformation,color.r, color.g, color.b, color.a * (intersectY - int(intersectY)));
            SDL_RenderDrawPoint(RenderInformation, int(intersectY), x);
            SDL_SetRenderDrawColor(RenderInformation,color.r, color.g, color.b, color.a * (1 - (intersectY - int(intersectY))));
            SDL_RenderDrawPoint(RenderInformation, int(intersectY) - 1, x);
            intersectY += m;
        }
    }
    else
    {
        for(int x = x1; x <= x2; x++)
        {
            SDL_SetRenderDrawColor(RenderInformation,color.r, color.g, color.b, color.a * (intersectY - int(intersectY)));
            SDL_RenderDrawPoint(RenderInformation,x, int(intersectY));
            SDL_SetRenderDrawColor(RenderInformation,color.r, color.g, color.b, color.a * (1 - (intersectY - int(intersectY))));
            SDL_RenderDrawPoint(RenderInformation, x, int(intersectY) - 1);
            intersectY += m;
        }
    }
}

void DrawLineAntiAliasing(Vector2 v1, Vector2 v2, Color color)
{
    DrawLineAntiAliasing(v1.x, v1.y, v2.x, v2.y, color);
}

void DrawLineAntiAliasing(int x1, int y1, int x2, int y2, Color color)
{
    DrawLineAntiAliasing(static_cast<float>(x1),static_cast<float>(y1),static_cast<float>(x2),static_cast<float>(y2),color);
}

void DrawLineAntiAliasing(Vector2Int v1, Vector2Int v2, Color color)
{
    DrawLineAntiAliasing(static_cast<float>(v1.x),static_cast<float>(v1.y),static_cast<float>(v2.x),static_cast<float>(v2.y),color);
}

void DrawLineCurve(int x1, int y1, int x2, int y2, Color color, Curve curve, float curveHeight)
{
    SDL_SetRenderDrawColor(RenderInformation,color.r, color.g, color.b, color.a);
    float m = Vector2::Slope({x1,y1},{x2,y2});
    float m2 = m + M_PI / 2; //90deg angle.
    
    int i = 0;
    Vector2 posLine1 = {x1 + i, y1 + i * m};
    Vector2 posLine2 = Vector2::Zero();
    while(i < x2 - x1)
    {
        posLine2 = {x1 + i + 1, y1 + (i + 1) * m};
        //float steepness = Vector2::Slope(posLine1,posLine2);
        float pros = (float)i / (float)(x2 - x1);
        
        Vector2 offDir = Vector2(cos(m2),sin(m2));
        Vector2 targetPos = posLine1 + (offDir * curve.GetValue(pros) * curveHeight); 
        SDL_RenderDrawPoint(RenderInformation, targetPos.x, targetPos.y);
        
        i++;
        posLine1 = posLine2;
    }
}

void DrawLineCurve(float x1, float y1, float x2, float y2, Color color, Curve curve, float curveHeight)
{
    DrawLineCurve((int)x1, (int)y1, (int)x2, (int)y2, color, curve, curveHeight);
}

void DrawLineCurve(Vector2 v1, Vector2 v2, Color color, Curve curve, float curveHeight)
{
    DrawLineCurve((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, color, curve, curveHeight);
}

void DrawLineCurve(Vector2Int v1, Vector2Int v2, Color color, Curve curve, float curveHeight)
{
    DrawLineCurve(v1.x, v1.y, v2.x, v2.y, color, curve, curveHeight);
}

void DrawLineCurve(int x1, int y1, int x2, int y2, ColorGradient color, Curve curve, float curveHeight)
{
    float m = Vector2::Slope({x1,y1},{x2,y2});
    float m2 = m + M_PI / 2; //90deg angle.
    
    int i = 0;
    Vector2 posLine1 = {x1 + i, y1 + i * m};
    Vector2 posLine2 = Vector2::Zero();
    while(i < x2 - x1)
    {
        posLine2 = {x1 + i + 1, y1 + (i + 1) * m};
        //float steepness = Vector2::Slope(posLine1,posLine2);
        float pros = (float)i / (float)(x2 - x1);
        
        Vector2 offDir = Vector2(cos(m2),sin(m2));
        Vector2 targetPos = posLine1 + (offDir * curve.GetValue(pros) * curveHeight);
        Color c = color.GetColor(pros);
        //std::cout << "Pros: " << pros << " COLOR: " << c << std::endl;
        SDL_SetRenderDrawColor(RenderInformation, c.r, c.g, c.b, c.a);
        SDL_RenderDrawPoint(RenderInformation, targetPos.x, targetPos.y);
        posLine1 = posLine2;
        i++;
    }
}

void DrawLineCurve(float x1, float y1, float x2, float y2, ColorGradient color, Curve curve, float curveHeight)
{
    DrawLineCurve((int)x1, (int)y1, (int)x2, (int)y2, color, curve, curveHeight);
}

void DrawLineCurve(Vector2 v1, Vector2 v2, ColorGradient color, Curve curve, float curveHeight)
{
    DrawLineCurve((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, color, curve, curveHeight);
}

void DrawLineCurve(Vector2Int v1, Vector2Int v2, ColorGradient color, Curve curve, float curveHeight)
{
    DrawLineCurve(v1.x, v1.y, v2.x, v2.y, color, curve, curveHeight);
}

void renderFrame(Component *root, double elapsed)
{
    // ----- Draw background ----- //
    SDL_SetRenderDrawColor(RenderInformation, backgroundColour[0], backgroundColour[1], backgroundColour[2], 255);
    SDL_RenderClear(RenderInformation); //Fills the screen with the background colour
    
    for(int i = 290; i < 300; i++)
    {
        DrawLineSimple(i,195,i,1000,{200,200,200,255});
    }

    //White, blue white.
    ColorGradient cg1 = ColorGradient(
        Curve({CurveKey(0.0f, 1.0f, Tangent(),Tangent(Tangent::Interpolation::Constant)),CurveKey(5.0f/18.0f, 0.0f,Tangent(),Tangent(Tangent::Interpolation::Constant)), CurveKey(8.0f/18.0f, 1.0f,Tangent(),Tangent(Tangent::Interpolation::Constant))}),
        Curve({CurveKey(0.0f, 1.0f, Tangent(),Tangent(Tangent::Interpolation::Constant)),CurveKey(5.0f/18.0f, 47.0f / 255.0f,Tangent(),Tangent(Tangent::Interpolation::Constant)), CurveKey(8.0f/18.0f, 1.0f,Tangent(),Tangent(Tangent::Interpolation::Constant))}),
        Curve({CurveKey(0.0f, 1.0f, Tangent(),Tangent(Tangent::Interpolation::Constant)),CurveKey(5.0f/18.0f, 108.0f / 255.0f,Tangent(),Tangent(Tangent::Interpolation::Constant)), CurveKey(8.0f/18.0f, 1.0f,Tangent(),Tangent(Tangent::Interpolation::Constant))}),
        Curve::One()
    );
    ColorGradient cg2 = ColorGradient(Color(0,47,108,255)); //Blue

    float scale = 20.0f;
    Vector2 size = {18,11};
    Vector2 pos = {300,200};
    Vector2 end = {300 + size.x * scale,200};
    float CurveHeight = 40.0f;
    Curve c = Curve();

    float count = 20.0f;
    for(float i = 0.0f; i < count; i += 1.0f / count)
    {
        c.keys.push_back(CurveKey(i, i * sin(3.0f * elapsed + i * M_PI)));
    }

    for(int i = 0; i < size.y * scale / 4.0f; i++)
    {
        DrawLineCurve(pos + Vector2::Up() * i,end + Vector2::Up() * i,cg1,c,CurveHeight);
    }
    pos += Vector2::Up() * size.y * scale / 4.0f;
    end += Vector2::Up() * size.y * scale / 4.0f;
    for(int i = 0; i < size.y * scale / 3.0f; i++)
    {
        DrawLineCurve(pos + Vector2::Up() * i,end + Vector2::Up() * i,cg2,c,CurveHeight);
    }
    
    pos += Vector2::Up() * size.y * scale / 4.0f;
    end += Vector2::Up() * size.y * scale / 4.0f;
    for(int i = 0; i < size.y * scale / 4.0f; i++)
    {
        DrawLineCurve(pos + Vector2::Up() * i,end + Vector2::Up() * i,cg1,c,CurveHeight);
    }

    SDL_RenderPresent(RenderInformation); //Draws things.
}

#endif