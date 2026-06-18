#ifndef _SPRITEH_
#define _SPRITEH_

#include <SDL2/SDL_image.h>
#include <iostream>

struct Sprite
{

    enum Splicing
    {
        GridByCellSize,
        GridByCellCount,
    };

    Splicing splicingMethod = GridByCellCount;

    //For cell size -> (width or height) of cell in pixels; for cell count -> (horizontal / vertical) count of cells
    int countHor = 1;
    int countVer = 1;

    char imageName[128];
    int currentIndex = 0; //Which image of the spritesheet is used.
    SDL_Surface *sourceImage;

    void loadSprite(const char* path)
    {
        char buffer[128];
        strcpy(buffer, "src/Game/Sprites/");
        strcat(buffer, path);
        
        strcpy(imageName, path);
        sourceImage = IMG_Load(buffer);
        if(!sourceImage)
        {
            SDL_Log("IMG_Load failed: %s", IMG_GetError());
        }
    }

    int CellCount()
    {
        switch (splicingMethod)
        {
            case Splicing::GridByCellCount:
                return countHor * countVer;

            case Splicing::GridByCellSize:
                if(sourceImage != NULL)
                {
                    return ((int)sourceImage->w / countHor) * ((int)sourceImage->h / countVer);
                }
                return 1; //Missing image will be treated as singular image.

            default:
                return 1; //Missing image will be treated as singular image.
        }
    }

    SDL_Rect GetSrcRect(int index)
    {
        if(sourceImage == NULL)
        {
            std::cout << "Missing image source of " << imageName << std::endl;
            return {0,0,0,0};
        }

        switch (splicingMethod)
        {
            case Splicing::GridByCellCount:
            {
                int cellWidth = (sourceImage->w - sourceImage->w % countHor) / countHor;
                int cellHeight = (sourceImage->h - sourceImage->h % countVer) / countVer;
                int column = index % countHor;
                int row = (index - column) / countHor;
                SDL_Rect rect = {column * cellWidth, row * cellHeight, cellWidth, cellHeight};
                return rect;
            }
                
            case Splicing::GridByCellSize:
            {
                int cellCountHor = ((int)sourceImage->w / countHor);
                int cellCountVer = ((int)sourceImage->h / countVer);
                int column = index % cellCountHor;
                int row = index / cellCountVer;
                SDL_Rect rect = {column * cellCountHor, row * cellCountVer, countHor, countVer};
                return rect;
            }
                
            default:
                std::cout << "Invalid splicing method" << std::endl;
                return {0,0,0,0};
        }
    }
};

#endif