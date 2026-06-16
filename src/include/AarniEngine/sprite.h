#ifndef _SPRITEH_
#define _SPRITEH_

#include <SDL2/SDL_image.h>

SDL_Surface loadTexture(const char* path)
{
    char buffer[128];
    strcpy(buffer, "src/Game/Sprites/");
    strcat(buffer, path);
    SDL_Surface* surface = IMG_Load(buffer);
    if (!surface) {
        SDL_Log("IMG_Load failed: %s", IMG_GetError());
        return;
    }
    return *surface;
}


SDL_Texture getSprite(SDL_Surface surface, SDL_Rect rect)
{
    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(RenderInformation, surface);
    SDL_FreeSurface(surface);
    return texture;
}


#endif