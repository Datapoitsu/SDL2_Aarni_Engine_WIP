#include <SDL2/SDL.h>
#include <string.h>

struct Buttons{
    SDL_KeyCode keys[3];
    bool isPressed[3] = {false,false,false};
};

//Action is something that you would see in binding settings as an action.
struct Action{
    char name[20];
    struct Buttons buttons[2];
};

Action actions[] = {
    {
        {"Up"},
        {
            {
                {SDLK_w,SDLK_UNKNOWN,SDLK_UNKNOWN},
            },
            {
                {SDLK_UP,SDLK_UNKNOWN,SDLK_UNKNOWN},
            }
        }
    },
    {
        {"Down"},
        {
            {
                {SDLK_s,SDLK_UNKNOWN,SDLK_UNKNOWN},
            },
            {
                {SDLK_DOWN,SDLK_UNKNOWN,SDLK_UNKNOWN},
            }
        }
    },
    {
        {"Left"},
        {
            {
                {SDLK_a,SDLK_UNKNOWN,SDLK_UNKNOWN},
            },
            {
                {SDLK_LEFT,SDLK_UNKNOWN,SDLK_UNKNOWN},
            }
        }
    },
    {
        {"Right"},
        {
            {
                {SDLK_d,SDLK_UNKNOWN,SDLK_UNKNOWN},
            },
            {
                {SDLK_RIGHT,SDLK_UNKNOWN,SDLK_UNKNOWN},
            }
        }
    }
};

void UpdateInputs(SDL_Event e)
{
    for(int i = 0; i < sizeof(actions) / sizeof(actions[0]); i++)
    {
        for(int k = 0; k < 2; k++)
        {
            for(int j = 0; j < 3; j++)
            {
                if (e.key.keysym.sym == actions[i].buttons[k].keys[j])
                {
                    if(e.type == SDL_KEYDOWN) //Key pressed down
                    {
                        actions[i].buttons[k].isPressed[j] = true;
                    }
                    if(e.type == SDL_KEYUP) //Key pressed up
                    {
                        actions[i].buttons[k].isPressed[j] = false;
                    }
                }
            }
        }
    }
}

bool GetAction(struct Action a){
    for(int i = 0; i < 2; i++)
    {
        //No binding.
        bool emptyButtons = true;
        for(int k = 0; k < 3; k++){
            if(a.buttons[i].keys[k] != SDLK_UNKNOWN){
                emptyButtons = false;
                break;
            }
        }
        if(emptyButtons == true){
            continue;
        }
        
        //Check buttons
        bool isPressed = true;
        for(int k = 0; k < 3; k++){
            //If non-empty button isn't pressed, then no input
            if(a.buttons[i].keys[k] != SDLK_UNKNOWN && a.buttons[i].isPressed[k] == false){
                isPressed = false;
                break;
            }
        }
        if(isPressed){
            return true;
        }
    }

    return false;
}

bool GetActionByName(std::string name){
    for(int i = 0; i < sizeof(actions) / sizeof(actions[0]); i++){
        if(actions[i].name == name){
            return GetAction(actions[i]);
        }
    }
    printf("Couldn't find an input for action named: %s",name);
    return false;
};

bool GetActionDown(Action a){
    return false;
}

bool GetActionUp(Action a){
    return false;
}