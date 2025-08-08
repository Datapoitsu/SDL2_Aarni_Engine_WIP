#ifndef _BALLH_
#define _BALLH_

#include <AarniEngine/component.h>

class Ball: public Component
{
    public:
        Vector3 velocity = {0,0,0};
        float radius = 25.0f;
        SDL_Color color = {(Uint8)(rand() % 256), (Uint8)(rand() % 256), (Uint8)(rand() % 256)};

        void Start() override
        {
            componentType = ball;
        }

        void Update(double deltaTime) override
        {
            velocity.y -= 9.81;
            dynamic_cast<Transform*>(parent)->position += velocity * deltaTime;
            if(dynamic_cast<Transform*>(parent)->position.y < 0)
            {
                velocity.y *= -0.9f;
                dynamic_cast<Transform*>(parent)->position.y *= -1;
            }
        }
};

#endif