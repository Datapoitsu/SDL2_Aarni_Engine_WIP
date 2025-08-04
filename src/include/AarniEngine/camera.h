#ifndef _CUSTOMCOMPONENTH_
#define _CUSTOMCOMPONENTH_

#include <AarniEngine/component.h>
#include <AarniEngine/renderEngine.h>
#include <AarniEngine/mat4x4.h>

class Camera: public Component
{
    public:
        float fNear = 0.1f;
        float fFar = 1000.0f;
        float fFov = 90.0f;
        float fAspectRatio = screenWidth / screenHeigth;
        float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
        Mat4x4 projectionMatrix = {};
        
        void Start() override
        {
            componentType = camera;

            projectionMatrix.m[0][0] = fAspectRatio * fFovRad;
            projectionMatrix.m[1][1] = fFovRad;
            projectionMatrix.m[2][2] = fFar / (fFar - fNear);
            projectionMatrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
            projectionMatrix.m[2][3] = 1.0f;
            projectionMatrix.m[3][3] = 0.0f;
        }

        void Update(double deltaTime) override
        {
            
        }
};

#endif

