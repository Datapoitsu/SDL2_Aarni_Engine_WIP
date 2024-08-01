#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <AarniEngine/input.h>
#include <AarniEngine/vector.h>
#include <AarniEngine/sprite.h>

#define PI 3.141592654

//Function declaration
void Update(float deltaTime);
void Start();
void createWindow();
void UpdateRendering();

//Application variables
SDL_Window *window;
SDL_Renderer *renderer;
const int width = 400, heigth = 400;
bool endApp = false;

// Time calculation
timeval t1, t2;
double elapsedTime;
double deltaTime;
int fpsLimiter = 60;

struct Unit{
    SDL_Rect rect;
    SDL_Rect dstrect;
    SDL_Texture *sprite;
    Vector position = {width / 2, heigth / 2, 0};
    float movementSpeed = 200;
    float jumpForce = 10;
    double jumpTimer = 0; 
};

Unit a;

int main(int argc, char *argv[])
{
    createWindow();
    if(window == NULL){
        return 1;
    }

    Start();

    //Begining of calculating time.
    mingw_gettimeofday(&t1, NULL); 

    while (true)
    {
        //Ending application.
        SDL_Event Event;
        if (SDL_PollEvent(&Event))
        {
            if (SDL_QUIT == Event.type)
            {
                endApp = true;
            }
        }
        if(endApp)
        {
            break;
        }

        UpdateInputs(Event);

        Update(deltaTime); //Write into updata function things that should repeat every frame.

        UpdateRendering();

        //fps limiter
        Sleep(std::max(0.0,(1000 / fpsLimiter) - (deltaTime * 1000)));

        //Calculating passing time.
        mingw_gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        deltaTime = elapsedTime / 1000;
        t1 = t2;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}

void createWindow()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("SDL Practice",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,heigth,SDL_WINDOW_ALLOW_HIGHDPI);

    if (window != NULL)
    {
        renderer = SDL_CreateRenderer(window, -1, 0);
    }
    else
    {
        std::cout << "Could now create window: " << SDL_GetError() << std::endl;
    }
}

void QuitApplication(){
    endApp = true;
}

void Start(){
    /*
    a.rect = {32,32,32,32};
    a.sprite = IMG_LoadTexture(renderer, "src/Game/Sprites/hahmo.png");
    a.dstrect = {0,0,16,16};
    */

    Texture T;
    T.texture = IMG_LoadTexture(renderer, "src/Game/Sprites/hahmo.png");
    SplitTexture(&T,*T.sprites,2,2);


    a.rect = {32,32,32,32};
    a.sprite = T.texture;
    a.dstrect = *T.sprites[0];

    /*
    Texture T;
    T.texture = IMG_LoadTexture(renderer, "src/Game/Sprites/hahmo.png");
    SplitTexture(&T,T.sprites,2,2);
    a.sprite = T.texture;
    a.dstrect = *T.sprites[2];
    for(int i = 0; i < 4; i++){
        SDL_Rect r = *T.sprites[i];
        std::cout << "Main " << i << ": " << r.x << "," << r.y << "," << r.w << "," << r.h << std::endl;
    }
    */
}

void Update(float deltaTime)
{
    Vector direction = {0,0,0};
    if(GetActionByName("Up")){
        direction.y -= 1;
    }
    if(GetActionByName("Down")){
        direction.y += 1;
    }
    if(GetActionByName("Left")){
        direction.x -= 1;
    }
    if(GetActionByName("Right")){
        direction.x += 1;
    }

    normalize(&direction);

    a.position.x += direction.x * deltaTime * a.movementSpeed;
    a.position.y += direction.y * deltaTime * a.movementSpeed;
    a.rect.x = round(a.position.x);
    a.rect.y = round(a.position.y);
}

void UpdateRendering()
{
    SDL_RenderClear(renderer); 
    SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
    SDL_RenderCopy(renderer, a.sprite, &a.dstrect, &a.rect);
    SDL_RenderPresent(renderer);
}