#ifndef _RENDERERH_
#define _RENDERERH_

#include <AarniEngine/component.h>
#include <AarniEngine/mesh.h>

class Renderer: public Component
{
    public:
        enum ComponentType componentType = renderer;
        Mesh mesh;
        void Start() override
        {
            
        }

        void Update() override
        {
            SDL_SetRenderDrawColor(RenderInformation, 125, 125, 125, 255);

            SDL_Vertex vertex_1 = {{0, 0}, {255,0,0}, {1, 1}}; //Center vertex
            SDL_Vertex vertex_2 = {{200,200},{255,0,0}, {1, 1}};
            SDL_Vertex vertex_3 = {{200,0},{255,0,0}, {1, 1}};
            SDL_Vertex vertices[] = {vertex_1,vertex_2,vertex_3};
            SDL_RenderGeometry(RenderInformation, NULL, vertices, 3, NULL, 0);

            SDL_RenderPresent(RenderInformation);
            SDL_RenderClear(RenderInformation); //Clear afterwards
        }
};

#endif