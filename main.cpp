#include <AarniEngine/engine.h>

void Start() //This function is called at the start of the app.
{

}

void Update() //This function is called at every frame.
{
    if(GetActionDownByName("up"))
    {
        std::cout << "up" << std::endl;
    }
    if(GetActionDownByName("down"))
    {
        std::cout << "down" << std::endl;
    }
    if(GetActionDownByName("right"))
    {
        std::cout << "right" << std::endl;
    }
    if(GetActionDownByName("left"))
    {
        std::cout << "left" << std::endl;
    }
    if(GetActionDownByName("activate"))
    {
        std::cout << "activate" << std::endl;
    }
}