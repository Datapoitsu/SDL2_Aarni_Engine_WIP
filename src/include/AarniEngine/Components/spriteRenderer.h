#ifndef _CUSTOMCOMPONENTH_
#define _CUSTOMCOMPONENTH_

#include <AarniEngine/component.h>
#include <AarniEngine/sprite.h>
#include <AarniEngine/renderEngine.h>

class SpriteRenderer: public Component
{
    public:
        Sprite sprite;
        void Start() override
        {
            componentType = spriteRenderer;
        }

        void Update(double deltaTime)
        {
            
        }
};

#endif