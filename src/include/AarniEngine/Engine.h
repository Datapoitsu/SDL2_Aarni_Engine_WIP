#ifndef _ENGINEH_
#define _ENGINEH_

//Windows libraries.
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <vector>

//My own libraries
#include <AarniEngine/input.h>
#include <AarniEngine/vector.h>
#include <AarniEngine/transform.h>
#include <AarniEngine/mesh.h>
#include <AarniEngine/renderEngine.h>
#include <AarniEngine/component.h>
#include <AarniEngine/renderer.h>

struct GameObject
{
    char name[32] = "";
    std::vector<Component*> components;
};

std::vector<GameObject> hierarchy; //List of all gameobjects in the game

//Function declaration
void Start();
void Update();

bool endApp = false;

// ----- Time ----- //
timeval t1, t2; //Time at start and end of the frame
double elapsedTime;
double deltaTime;
int fpsLimiter = 60;

int main(int argc, char *argv[])
{
    if(createWindow() == false)
    {
        return 1;
    }

    Start();
    //Calls update on all components
    for(int objectIndex = 0; objectIndex < hierarchy.size(); objectIndex++)
    {
        for(int componentIndex = 0; componentIndex < hierarchy[objectIndex].components.size(); componentIndex++)
        {
            hierarchy[objectIndex].components[componentIndex]->Start();
            if(Transform* T = dynamic_cast<Transform*>(hierarchy[objectIndex].components[componentIndex]))
            {
                std::cout << *T << std::endl;
            }
        }
    }

    //Begining of calculating time.
    mingw_gettimeofday(&t1, NULL); 

    while (true)
    {
        //Ending application.
        SDL_Event Event;
        if (SDL_PollEvent(&Event))
        {
            if (SDL_QUIT == Event.type)
            {
                endApp = true;
            }
        }
        if(endApp)
        {
            break;
        }

        UpdateInputs(Event);

        //Calls Update function on all components
        for(int objectIndex = 0; objectIndex < hierarchy.size(); objectIndex++)
        {
            for(int componentIndex = 0; componentIndex < hierarchy[objectIndex].components.size(); componentIndex++)
            {
                hierarchy[objectIndex].components[componentIndex]->Update();
            }
        }

        UpdatePreviousInputs(Event); //Updates previousinputs, used for keyUp and keyDown functions

        renderFrame();

        //fps limiter
        Sleep(std::max(0.0,(1000 / fpsLimiter) - (deltaTime * 1000)));

        //Calculating passing time.
        mingw_gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        deltaTime = elapsedTime / 1000;
        t1 = t2;
    }

    closeWindow();
    return 1;
}

void QuitApplication(){
    endApp = true;
}

#endif