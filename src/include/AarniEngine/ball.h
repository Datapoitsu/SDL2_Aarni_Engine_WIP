#ifndef _BALLH_
#define _BALLH_

#include <AarniEngine/component.h>

class Ball: public Component
{
    public:
        Vector3 velocity = {0,0,0};
        float radius = 25.0f;
        SDL_Color color = {-256 + rand() % 512, -256 + rand() % 512, -256 + rand() % 512};
        float speed = 128.0f;
        void Start() override
        {
            componentType = ball;
            velocity = {(rand() % 2) * 2 - 1, (rand() / rand()) * (rand() % 2 * 2 - 1), 0};
            velocity *= speed;
        }

        void Update(double deltaTime) override
        {
            dynamic_cast<Transform*>(parent)->position += velocity * deltaTime;
        }
};

#endif