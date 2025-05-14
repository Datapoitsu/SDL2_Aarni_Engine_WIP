#include <AarniEngine/engine.h>
#include <AarniEngine/renderer.h>
#include <AarniEngine/transform.h>
void Start() //This function is called at the start of the app.
{
    Renderer* r = new Renderer();
    Transform* t = new Transform();
    hierarchy.push_back(
    {
        "Kuutio",
        {t,r},
    });
}