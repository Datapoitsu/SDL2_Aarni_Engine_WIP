#ifndef _CUSTOMCOMPONENTH_
#define _CUSTOMCOMPONENTH_

#include <AarniEngine/component.h>

class CustomComponent: public Component
{
    public:
        void Start() override
        {
            //enum ComponentType componentType = customtype;
            //Remember to add the custom type to component.h !!!
        }

        void Update(double deltaTime) override
        {

        }
};

#endif