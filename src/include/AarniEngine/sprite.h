#include <SDL2/SDL_image.h>

struct Texture{
    SDL_Texture *texture = NULL;
    SDL_Rect *sprites[];
};

void LoadSpriteSplit(Texture *Tex, int hor, int ver)
{

}

void SplitTexture(Texture *Tex, SDL_Rect sprites[], int hor, int ver){
    SDL_Rect s[hor * ver];
    

    //Collects width & heigth of the texture.
    int imgW, imgH = 0;
    SDL_QueryTexture(Tex->texture, NULL, NULL, &imgW, &imgH);

    int sw,sh = 0; //sprite width & height
    sw = imgW / hor;
    sh = imgH / ver;

    for(int v = 0; v < ver; v++)
    {
        for(int h = 0; h < hor; h++)
        {
            s[h + v * hor] = {h * sw, v * sh, sw, sh};
            std::cout << h + v * hor << ". " << s[h + v * hor].x << ", " << s[h + v * hor].y << ", " << s[h + v * hor].w << ", " << s[h + v * hor].h << std::endl;
        }
    }
    sprites = s;
}

/*
void SplitTexture(Texture *Tex, SDL_Rect *sprites[], int horizontalCount, int verticalCount)
{
    //Collects width & heigth of the texture.
    int w, h = 0;
    SDL_QueryTexture(Tex->texture, NULL, NULL, &w, &h);
    sprites = (SDL_Rect**)malloc(sizeof(SDL_Rect) * horizontalCount * verticalCount);
    
    for(int y = 0; y < verticalCount; y++)
    {
        for(int x = 0; x < horizontalCount; x++)
        {
            sprites[0].x = 0;
            sprites[y * horizontalCount + x].x = x * (w / horizontalCount);
            y * (h / verticalCount), w / horizontalCount, h / verticalCount};
            std::cout << y * horizontalCount + x << ": " << r.x << "," << r.y << "," << r.w << "," << r.h << std::endl;
        }
    }
    std::cout << "Size: " << sizeof(sprites) / sizeof(sprites[0]) << std::endl;
}
*/