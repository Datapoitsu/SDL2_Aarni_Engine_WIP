#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <AarniEngine/input.h>
#include <AarniEngine/vector.h>
#include <AarniEngine/sprite.h>
#include <AarniEngine/transform.h>
#include <AarniEngine/mesh.h>

//Function declaration
void Update(float deltaTime);
void Start();
void createWindow();
void UpdateRendering();

//Application variables
SDL_Window *window;
SDL_Renderer *renderer;
const int width = 1000, heigth = 1000;
bool endApp = false;

// Time calculation
timeval t1, t2;
double elapsedTime;
double deltaTime;
int fpsLimiter = 60;

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

        UpdatePreviousInputs(Event); //Updates previousinputs, used for keyUp and keyDown functions

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

void UpdateRendering()
{
    SDL_RenderClear(renderer); 
    SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
    SDL_RenderPresent(renderer);
}