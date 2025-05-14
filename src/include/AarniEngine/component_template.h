#ifndef _CUSTOMCOMPONENTH_
#define _CUSTOMCOMPONENTH_

#include <AarniEngine/component.h>

class Renderer: public Component
{
    public: 
        void Start() override
        {
            std::cout << "Startti toimii!" << std::endl;
        }

        void Update() override
        {
            std::cout << "Update toimii!" << std::endl;
        }
};

#endif