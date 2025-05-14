#ifndef _RENDERERH_
#define _RENDERERH_

#include <AarniEngine/component.h>

class Renderer: public Component
{
    public: 
        void Start() override
        {
            std::cout << "Startti toimii" << std::endl;
        }

        void Update(float deltaTime) override
        {
            std::cout << "Update toimii!" << std::endl;
        }
};

#endif