#ifndef _CIRCLECOLLIDERH_
#define _CIRCLECOLLIDERH_

#include <AarniEngine/component.h>

class CircleCollider: public Component
{
    public:
        float radius = 10.0f;
        Vector2 offset = {0,0};
        void Start() override
        {
            componentType = circleCollider2D;
        }

        void Update(double deltaTime) override
        {

        }

        void OnCollisionEnter()
        {
            std::cout << "COLLIDING!" << std::endl;
        }
};

#endif