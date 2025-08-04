#ifndef _CUSTOMCOMPONENTH_
#define _CUSTOMCOMPONENTH_

#include <AarniEngine/component.h>

class CustomComponent: public Component
{
    enum ComponentType componentType = empty;
    public:
        void Start() override
        {
            std::cout << "Startti toimii!" << std::endl;
        }

        void Update(double deltaTime) override
        {
            std::cout << "Update toimii!" << std::endl;
        }
};

#endif