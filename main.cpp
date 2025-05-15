#include <AarniEngine/engine.h>
#include <AarniEngine/renderer.h>
#include <AarniEngine/transform.h>

void Start() //This function is called at the start of the app.
{
    Transform* t = new Transform();
    Renderer* r = new Renderer();
    hierarchy.push_back(
    {
        "Kuutio",
        {t,r},
    });
}