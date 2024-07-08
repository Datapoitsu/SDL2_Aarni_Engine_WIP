#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define PI 3.141592654

const int WIDTH = 400, HEIGHT = 400;

SDL_Texture *img = NULL;
int w, h; // texture width & height

float dist = 100;
float playerRot;

// Time calculation
timeval t1, t2;
double elapsedTime;
double deltaTime;
int fpsLimiter = 60;

int main( int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("SDL Practice",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == NULL)
    {
        std::cout << "Could now create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    img = IMG_LoadTexture(renderer, "src/Game/Sprites/hahmo.png");
	SDL_QueryTexture(img, NULL, NULL, &w, &h);
	
    SDL_Event windowEvent;
    
    //Begining of calculating time.
    mingw_gettimeofday(&t1, NULL); 

    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }

        playerRot += deltaTime * PI * 2;

        SDL_Rect texr; texr.x = cos(playerRot) * dist + (WIDTH / 2); texr.y = sin(playerRot) * dist + (HEIGHT / 2); texr.w = w; texr.h = h; 
        SDL_RenderClear(renderer); 
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderCopy(renderer, img, NULL, &texr);
        SDL_RenderPresent(renderer);

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