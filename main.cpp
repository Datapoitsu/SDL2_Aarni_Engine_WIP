#include <AarniEngine/engine.h>

void Start() //This function is called at the start of the app.
{

}

void Update() //This function is called at every frame.
{
    /*
    if(GetActionByName("up"))
    {
        std::cout << "up" << std::endl;
    }
    if(GetActionByName("down"))
    {
        std::cout << "down" << std::endl;
    }
    if(GetActionByName("right"))
    {
        std::cout << "right" << std::endl;
    }
    if(GetActionByName("left"))
    {
        std::cout << "left" << std::endl;
    }*/
    if(GetActionByName("activate"))
    {
        std::cout << "activate" << std::endl;
    }
    /*if(GetActionByName("crouch"))
    {
        std::cout << "crouch" << std::endl;
    }*/
    
}