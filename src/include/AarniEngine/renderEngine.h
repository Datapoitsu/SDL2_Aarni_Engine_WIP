#ifndef _RENDERENGINE_
#define _RENDERENGINE_

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <AarniEngine/component.h>
#include <AarniEngine/ball.h>

//Application variables
SDL_Window *Window;
SDL_Renderer *RenderInformation;
const int screenWidth = 1000;
const int screenHeigth = 1000;
int backgroundColour[3] = {125,125,125};
void DrawRecursive(Component *c, Transform *t);
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

void DrawTriangle(SDL_Vertex vertices[], SDL_Texture *texture = NULL)
{
    SDL_RenderGeometry(RenderInformation, texture, vertices, 3, NULL, 0);
}

void DrawCircle(int posX, int posY, float radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(RenderInformation,color.r, color.g, color.b, color.a);
    if(radius <= 0){ return; }
    if(radius == 1) //Edge case where the other part of the code isn't able to draw a circle with a radius of one.
    {
        SDL_RenderDrawPoint(RenderInformation,posX,posY);
    }
    for(int vertical = 0; vertical < radius + 1; vertical++)
    {
        for(int horizontal = 0; horizontal < radius + 1; horizontal++)
        {
            if(sqrt(pow(-radius + vertical,2) + pow(-radius + horizontal,2)) < radius)
            {
                for(int fillHorizontal = 0; fillHorizontal < radius * 2 - horizontal * 2; fillHorizontal++)
                {
                    SDL_RenderDrawPoint(RenderInformation,posX - radius + horizontal + fillHorizontal, posY - radius + vertical);
                    SDL_RenderDrawPoint(RenderInformation,posX - radius + horizontal + fillHorizontal, posY + radius - vertical);
                }
                break;
            }
        }
    }
}


void renderFrame(Component *root)
{
    // ----- Draw background ----- //
    SDL_SetRenderDrawColor(RenderInformation, backgroundColour[0], backgroundColour[1], backgroundColour[2], 255);
    SDL_RenderClear(RenderInformation); //Fills the screen with the background colour

    // ----- Circle ----- //
    Transform *t1 = new Transform();
    DrawRecursive(root, t1);
    
    SDL_RenderPresent(RenderInformation); //Draws things.

    //Start from root.
    //Go through all components.
    //Calculate the current position
    //Render mesh when seen one.
    
    /*
    Mesh m = dynamic_cast<Renderer*>(Root->children[0]->children[1])->mesh;
    std::cout << "VertexCount: " << m.vertexCount << " FaceCount: " << m.faceCount << std::endl;
    for(int i = 0; i < m.faceCount; i++)
    {
        Face f;
        //Mat4x4::MultiplyMatrixVector(m.faces[i], *f.a, dynamic_cast<Camera*>(Root->children[1]->children[0].projectionMatrix));
    }
    */
}

// ----- Anchoring ----- //
void offsetAnchor(SDL_Rect *r, Renderer2D::AnchorPosition anchor)
{
    //Top left anchor is the default.
    if(anchor == Renderer2D::AnchorPosition::topLeft)
    {
        return;
    }
    //Right side move.
    if(     anchor == Renderer2D::AnchorPosition::topRight
        ||  anchor == Renderer2D::AnchorPosition::middleRight
        ||  anchor == Renderer2D::AnchorPosition::bottomRight
    )
    {
        r->x -= r->w;
    }
    else //Center horizontal move.
    if(     anchor == Renderer2D::AnchorPosition::topCenter
        ||  anchor == Renderer2D::AnchorPosition::middleCenter
        ||  anchor == Renderer2D::AnchorPosition::bottomCenter
    )
    {
        r->x -= (int)(r->w / 2);
    }
    //Bottom side move.
    if( anchor == Renderer2D::AnchorPosition::bottomLeft
        ||  anchor == Renderer2D::AnchorPosition::bottomCenter
        ||  anchor == Renderer2D::AnchorPosition::bottomRight
    )
    {
        r->y -= r->h;
    }
    else //Middle vertical move.
    if(     anchor == Renderer2D::AnchorPosition::middleLeft
        ||  anchor == Renderer2D::AnchorPosition::middleCenter
        ||  anchor == Renderer2D::AnchorPosition::middleRight
    )
    {
        r->y -= (int)(r->h / 2);
    }
}

void flippingRenderer(Renderer2D *r, SDL_RendererFlip *rf, double *angle)
{
    if(r->flipX && r->flipY)
    {
        *angle += 180;
        return;
    }
    else
    {
        if(r->flipX)
        {
            *rf = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
        }
        else if(r->flipY)
        {
            *rf = SDL_RendererFlip::SDL_FLIP_VERTICAL;
        }
    }
}

void DrawSprite(Renderer2D renderer2d, Transform *t)
{
    SDL_Rect destination;
    destination.x = t->position.x;
    destination.y = t->position.y;
    SDL_QueryTexture(renderer2d.sprite,NULL,NULL,&destination.w,&destination.h);
    destination.w *= t->scale.x;
    destination.h *= t->scale.y;
    offsetAnchor(&destination, renderer2d.anchor);
    
    SDL_SetTextureColorMod(renderer2d.sprite,renderer2d.colour.r,renderer2d.colour.g,renderer2d.colour.b);

    SDL_RendererFlip flipping = SDL_RendererFlip::SDL_FLIP_NONE;
    double angle = 0;
    flippingRenderer(&renderer2d, &flipping, &angle);

    SDL_RenderCopyEx(RenderInformation, renderer2d.sprite, NULL, &destination, angle, NULL, flipping);
}

void DrawRecursive(Component *c, Transform *t)
{
    if(c->componentType == transform)
    {
        *t += *dynamic_cast<Transform*>(c);
    }
    else if(c->componentType == renderer2d)
    {
        DrawSprite(*dynamic_cast<Renderer2D*>(c), t);
    }
    else if(c->componentType == ball)
    {
        DrawCircle(t->position.x, screenHeigth -50 -t->position.y -t->position.z / 2,dynamic_cast<Ball*>(c)->radius,dynamic_cast<Ball*>(c)->color);
    }
    for(int i = 0; i < c->childCount; i++)
    {
        Transform *t2 = new Transform();
        *t2 += *t;
        DrawRecursive(c->children[i], t2);
    }
}

#endif