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

    SDL_SetRenderDrawColor(RenderInformation,125,0,0,255);
    //SDL_RenderDrawLine(RenderInformation,400,400,500,450);
    // ----- Triangle ----- //
    
    SDL_Texture *texture = IMG_LoadTexture(RenderInformation,"src/Game/Sprites/BrickWall.png");
    
    SDL_Vertex vertex_1 = {{0,screenHeigth / 4}, {255,255,255}, {0, 0}}; //Center vertex
    SDL_Vertex vertex_2 = {{screenWidth / 2, 0},{255,255,255}, {1, 0}};
    SDL_Vertex vertex_3 = {{screenWidth / 2, screenHeigth / 2},{255,255,255}, {1, 1}};
    SDL_Vertex vertices[] = {vertex_1,vertex_2,vertex_3};
    DrawTriangle(vertices, texture);
    
    SDL_Vertex vertex_4 = {{0,screenHeigth / 4}, {255,255,255}, {0, 0}}; //Center vertex
    SDL_Vertex vertex_5 = {{screenWidth / 2, screenHeigth / 2},{255,255,255}, {1, 1}};
    SDL_Vertex vertex_6 = {{0,screenHeigth / 4 * 3},{255,255,255}, {0, 1}};
    SDL_Vertex vertices2[] = {vertex_4,vertex_5,vertex_6};
    DrawTriangle(vertices2, texture);

    SDL_Vertex vertex_7 = {{screenWidth,screenHeigth / 4}, {255,255,255}, {1, 0}}; //Center vertex
    SDL_Vertex vertex_8 = {{screenWidth / 2, 0},{255,255,255}, {0, 0}};
    SDL_Vertex vertex_9 = {{screenWidth / 2, screenHeigth / 2},{255,255,255}, {0, 1}};
    SDL_Vertex vertices3[] = {vertex_7,vertex_8,vertex_9};
    DrawTriangle(vertices3, texture);
    
    SDL_Vertex vertex_10 = {{screenWidth,screenHeigth / 4}, {255,255,255}, {1, 0}}; //Center vertex
    SDL_Vertex vertex_11 = {{screenWidth / 2, screenHeigth / 2},{255,255,255}, {0, 1}};
    SDL_Vertex vertex_12 = {{screenWidth,screenHeigth / 4 * 3},{255,255,255}, {1, 1}};
    SDL_Vertex vertices4[] = {vertex_10,vertex_11,vertex_12};
    DrawTriangle(vertices4, texture);
    
    // ----- Circle ----- //
    Transform *t1 = new Transform();
    DrawBallsRecusive(root, t1);
    
    SDL_RenderPresent(RenderInformation); //Draws things.

    //Start from root.
    //Go through all components.
    //Calculate the current position
    //Render mesh when seen one.
    
    
    Mesh m = dynamic_cast<Renderer*>(root->children[0]->children[1])->mesh;
    std::cout << "VertexCount: " << m.vertexCount << " FaceCount: " << m.faceCount << std::endl;
    for(int i = 0; i < m.faceCount; i++)
    {
        Face f;
        //Mat4x4::MultiplyMatrixVector(m.faces[i], *f.a, dynamic_cast<Camera*>(root->children[1]->children[0].projectionMatrix));
    }
    
}

void DrawBallsRecusive(Component *c, Transform *t)
{
    if(c->componentType == transform)
    {
        *t += *dynamic_cast<Transform*>(c);
    }
    else if(c->componentType == ball)
    {
        DrawCircle(t->position.x, screenHeigth -50 -t->position.y -t->position.z / 2,dynamic_cast<Ball*>(c)->radius,dynamic_cast<Ball*>(c)->color);
    }
    for(int i = 0; i < c->childCount; i++)
    {
        Transform *t2 = new Transform();
        *t2 += *t;
        DrawBallsRecusive(c->children[i], t2);
    }
}

#endif