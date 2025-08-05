#ifndef _PLAYERH_
#define _PLAYERH_

#include <AarniEngine/component.h>
#include <AarniEngine/input.h>
#include <string.h>

class Player: public Component
{
    public:
        std::string upInput;
        std::string downInput;
        float speed = 500;

        void Start() override
        {
            componentType = player;
        }

        void Update(double deltaTime) override
        {
            int movedir = 0;
            if(GetActionByName(upInput))
            {
                movedir -= 1;
            }
            if(GetActionByName(downInput))
            {
                movedir += 1;
            }
            
            dynamic_cast<Transform*>(parent)->position += {0,movedir * speed * deltaTime,0};
            if(dynamic_cast<Transform*>(parent)->position.y < dynamic_cast<Transform*>(parent)->scale.y / 2)
            {
                dynamic_cast<Transform*>(parent)->position.y = dynamic_cast<Transform*>(parent)->scale.y / 2;
            }
            if(dynamic_cast<Transform*>(parent)->position.y > screenHeigth - dynamic_cast<Transform*>(parent)->scale.y / 2)
            {
                dynamic_cast<Transform*>(parent)->position.y = screenHeigth - dynamic_cast<Transform*>(parent)->scale.y / 2;
            }
        }
};

#endif