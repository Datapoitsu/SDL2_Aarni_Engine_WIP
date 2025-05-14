#include <AarniEngine/engine.h>
#include <AarniEngine/renderer.h>

void Start() //This function is called at the start of the app.
{
    Renderer R;
    hierarchy.push_back(
    {
        "Kuutio",
        Transform_Empty,
        {&R},
    });
}

void Update(float deltaTime) //This function is called every frame.
{

}