#ifndef _RENDERENGINE_
#define _RENDERENGINE_

#include <SDL2/SDL.h>
#include <stdlib.h>

//Application variables
SDL_Window *Window;
SDL_Renderer *RenderInformation;
const int width = 1000, heigth = 1000;

bool createWindow()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Window = SDL_CreateWindow("SDL Practice",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,heigth,SDL_WINDOW_ALLOW_HIGHDPI);
    if (Window != NULL)
    {
        RenderInformation = SDL_CreateRenderer(Window, -1, 0);
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

void renderFrame()
{

}

#endif