#ifndef _RENDERENGINE_
#define _RENDERENGINE_

#include <SDL2/SDL.h>
#include <stdlib.h>

//Application variables
SDL_Window *window;
SDL_Renderer *renderer;
const int width = 1000, heigth = 1000;

bool createWindow()
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
    return window != NULL;
}

void closeWindow()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderFrame()
{
    SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);

    SDL_Vertex vertex_1 = {{0, 0}, {255,0,0}, {1, 1}}; //Center vertex
    SDL_Vertex vertex_2 = {{200,200},{255,0,0}, {1, 1}};
    SDL_Vertex vertex_3 = {{200,0},{255,0,0}, {1, 1}};
    SDL_Vertex vertices[] = {vertex_1,vertex_2,vertex_3};
    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer); //Clear afterwards
}

#endif