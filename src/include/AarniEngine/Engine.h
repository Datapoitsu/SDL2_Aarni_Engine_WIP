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

Component *Root = new Component(); //Root object. Every thing will be built on top of this. Components consists an array of child components.

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
    Root->Start();
    for(int i = 0; i < Root->childCount; i++)
    {
        Root->children[i]->Start();
        Root->children[i]->StartChildren();
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
        for(int i = 0; i < Root->childCount; i++)
        {
            Root->children[i]->Update();
            Root->children[i]->UpdateChildren();
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