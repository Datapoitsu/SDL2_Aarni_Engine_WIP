#ifndef _RENDERER2DH_
#define _RENDERER2DH_

#include <AarniEngine/component.h>
#include <SDL2/SDL_render.h>

class Renderer2D: public Component
{
    public:
        SDL_Texture *sprite;
        SDL_Color colour = {255,255,255};
        bool flipX, flipY = false;
        enum AnchorPosition
        {
            topLeft,
            topCenter,
            topRight,
            middleLeft,
            middleCenter,
            middleRight,
            bottomLeft,
            bottomCenter,
            bottomRight,
        };
        AnchorPosition anchor = middleCenter;

        void Start() override
        {
            componentType = renderer2d;
        }

        void Update(double deltaTime) override
        {

        }
};

#endif