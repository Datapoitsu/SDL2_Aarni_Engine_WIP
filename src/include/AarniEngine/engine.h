#ifndef _ENGINEH_
#define _ENGINEH_

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#ifdef __linux__
	#include <unistd.h>

    void Sleep(int milliseconds)
    {
        usleep(milliseconds*1000);
    }
#endif
#ifdef __MINGW32__
    #include <windows.h>
#endif

//SDL2
#include <SDL2/SDL.h>

//My own libraries
#include <AarniEngine/input.h>
#include <AarniEngine/vector.h>
#include <AarniEngine/color.h>
#include <AarniEngine/curve.h>
#include <AarniEngine/quaternion.h>
#include <AarniEngine/mat4x4.h>

#include <AarniEngine/component.h>

#include <AarniEngine/Components/transform.h>
#include <AarniEngine/Components/renderer.h>
#include <AarniEngine/Components/camera.h>
#include <AarniEngine/Components/circleCollider.h>
#include <AarniEngine/Components/ball.h>
#include <AarniEngine/Components/spriteRenderer.h>

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
clock_t t1, t2; //Time at start and end of the frame
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
    t1 = clock();
    
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
        renderFrame(root, sessionTime);

        //fps limiter
        Sleep(std::max(0.0,(1000 / fpsLimiter) - (deltaTime * 1000)));

        //Calculating passing time.
        t2 = clock();
        elapsedTime = ((double)(t2 - t1)) / ((double)CLOCKS_PER_SEC);
        deltaTime = elapsedTime;
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