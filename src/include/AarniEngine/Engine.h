#ifndef _ENGINEH_
#define _ENGINEH_

//Windows libraries.
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <vector>

//SDL2
#include <SDL2/SDL.h>

//My own libraries
#include <AarniEngine/input.h>
#include <AarniEngine/vector.h>
#include <AarniEngine/quaternion.h>
#include <AarniEngine/mat4x4.h>

#include <AarniEngine/component.h>

#include <AarniEngine/transform.h>
#include <AarniEngine/renderer.h>
#include <AarniEngine/camera.h>
#include <AarniEngine/circleCollider.h>
#include <AarniEngine/ball.h>

Component *root = new Component(); //root object. Every thing will be built on top of this. Components consists an array of child components.

#include <AarniEngine/renderEngine.h>
#include <AarniEngine/physicsEngine.h>
#include <AarniEngine/mesh.h>

//Function declaration
void Start();
void Update();
bool endApp = false;

// ----- Time ----- //
double deltaTime;
timeval t1, t2; //Time at start and end of the frame
double elapsedTime;
double sessionTime = 0; //Total time the session has been on.
int fpsLimiter = 60;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    std::cout << "Engine starting" << std::endl;
    
    if(createWindow() == false)
    {
        return 1;
    }

    ReadInputConfig();
    PrintAllActions();

    Start();
    //Calls update on all components
    root->StartRecursive();
    
    //Begining of calculating time.
    mingw_gettimeofday(&t1, NULL); 
    
    while (true)
    {
        SDL_Event Event;
        //Ending application.
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

        UpdateInputs();
        Update();
        UpdatePreviousInputs();
        root->UpdateRecursive(deltaTime);

        //PhysicsEngine();
        renderFrame(root);

        //fps limiter
        Sleep(std::max(0.0,(1000 / fpsLimiter) - (deltaTime * 1000)));

        //Calculating passing time.
        mingw_gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        deltaTime = elapsedTime / 1000;
        t1 = t2;
        sessionTime += deltaTime;
    }

    closeWindow();
    return 1;
}

void QuitApplication(){
    endApp = true;
}

#endif