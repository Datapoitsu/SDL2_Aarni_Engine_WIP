#ifndef _RENDERERH_
#define _RENDERERH_

#include <AarniEngine/component.h>
#include <AarniEngine/mesh.h>

class Renderer: public Component
{
    public:
        Mesh mesh;
        void Start() override
        {
            componentType = renderer;
        }

        void Update(double deltaTime) override
        {

        }
};

#endif