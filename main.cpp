#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define PI 3.141592654

const int WIDTH = 400, HEIGHT = 400;

// Time calculation
timeval t1, t2;
double elapsedTime;
double deltaTime;
int fpsLimiter = 60;

struct Unit{
    SDL_Rect rect;
    SDL_Texture *sprite;
    float posX = WIDTH / 2;
    float posY = HEIGHT / 2;
    float movementSpeed = 100;
};

struct Action{
    SDL_KeyCode Key;
    bool isPressed = false;
};

Action actions[]{
    Action{SDLK_w},
    Action{SDLK_s},
    Action{SDLK_a},
    Action{SDLK_d},
};

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("SDL Practice",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == NULL)
    {
        std::cout << "Could now create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    struct Unit Player = { {WIDTH / 2, HEIGHT / 2, 128, 128}, IMG_LoadTexture(renderer, "src/Game/Sprites/hahmo.png")};
    struct Unit floor = { {WIDTH / 2 - 128, HEIGHT / 2 + 100, 256, 32}, IMG_LoadTexture(renderer, "src/Game/Sprites/dot.png")};
	
    SDL_QueryTexture(Player.sprite, NULL, NULL, &Player.rect.w, &Player.rect.h);
	
    SDL_Event Event;
    
    //Begining of calculating time.
    mingw_gettimeofday(&t1, NULL); 

    while (true)
    {
        if (SDL_PollEvent(&Event))
        {
            if (SDL_QUIT == Event.type)
            {
                break;
            }

            for(int i = 0; i < sizeof(actions); i++){
                if (Event.key.keysym.sym == actions[i].Key){
                    if(Event.type == SDL_KEYDOWN){
                        actions[i].isPressed = true;
                    }
                    if(Event.type == SDL_KEYUP){
                        actions[i].isPressed = false;
                    }
                }
            }
        }

        float x = 0;
        float y = 0;
        if(actions[0].isPressed){
            y -= 1;
        }
        if(actions[1].isPressed){
            y += 1;
        }
        if(actions[2].isPressed){
            x -= 1;
        }
        if(actions[3].isPressed){
            x += 1;
        }
        
        //Normalize.
        float magnitude = sqrt(x*x + y*y);
        if(magnitude != 0){
            x /= magnitude;
            y /= magnitude;
        }
        
        Player.posX += x * deltaTime * Player.movementSpeed;
        Player.posY += y * deltaTime * Player.movementSpeed;
        Player.rect = {(int)Player.posX,(int)Player.posY,Player.rect.w,Player.rect.h};

        SDL_RenderClear(renderer); 
        SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
        SDL_RenderCopy(renderer, Player.sprite, NULL, &Player.rect);
        SDL_RenderCopy(renderer, floor.sprite, NULL, &floor.rect);
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