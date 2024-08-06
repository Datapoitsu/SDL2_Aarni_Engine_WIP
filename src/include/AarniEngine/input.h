#include <SDL2/SDL.h>
#include <string.h>

struct Buttons //Has all buttons for an action. Action can have more than one buttons struct.
{
    SDL_KeyCode keys[3];
    bool isPressed[3] = {false,false,false};
    bool previouslyPressed[3] = {false,false,false};
};

struct Action //Action is something that you would see in binding settings as an action.
{
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
    },
    {
        {"Activate"},
        {
            {
                {SDLK_e,SDLK_r,SDLK_q},
            },
            {
                {SDLK_UNKNOWN,SDLK_UNKNOWN,SDLK_UNKNOWN},
            }
        }
    }
};

void UpdateInputs(SDL_Event e) //Checks all defined actions and if the buttons are pressed.
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

void UpdatePreviousInputs(SDL_Event e) //Sets values for previously pressed buttons. Used for GetKeyUp & GetKeyDown.
{
    for(int i = 0; i < sizeof(actions) / sizeof(actions[0]); i++)
    {
        for(int k = 0; k < 2; k++)
        {
            for(int j = 0; j < 3; j++)
            {
                actions[i].buttons[k].previouslyPressed[j] = actions[i].buttons[k].isPressed[j];
            }
        }
    }
}

bool GetAction(struct Action a)
{
    for(int i = 0; i < 2; i++)
    {
        //Checks if there isn't any bindings.
        bool emptyButtons = true;
        for(int k = 0; k < 3; k++){
            if(a.buttons[i].keys[k] != SDLK_UNKNOWN){
                emptyButtons = false;
                break;
            }
        }
        if(emptyButtons == true) //Current actions had no binding at all.
        {
            continue;
        }
        
        //Check buttons.
        bool isPressed = true;
        for(int k = 0; k < 3; k++){
            //If non-empty button isn't pressed, then no input.
            if(a.buttons[i].keys[k] != SDLK_UNKNOWN && a.buttons[i].isPressed[k] == false){
                isPressed = false;
                break;
            }
        }
        if(isPressed)
        {
            return true;
        }
    }
    return false;
}

bool GetActionByName(std::string name) //Version with string.
{
    //Checks through all actions to find the correct action.
    for(int i = 0; i < sizeof(actions) / sizeof(actions[0]); i++){
        if(actions[i].name == name){
            return GetAction(actions[i]);
        }
    }
    printf("Couldn't find an input for action named: %s \n",name);
    return false;
};

bool GetActionDown(Action a) //Action down is the moment when key goes from up state to down state
{
    for(int i = 0; i < 2; i++)
    {
        //Checks if there isn't any bindings
        bool emptyButtons = true;
        for(int k = 0; k < 3; k++){
            if(a.buttons[i].keys[k] != SDLK_UNKNOWN){
                emptyButtons = false;
                break;
            }
        }
        if(emptyButtons == true) //Current actions had no binding at all.
        {
            continue;
        }
        
        //Check buttons
        bool isPressed = true;
        for(int k = 0; k < 3; k++)
        {
            //If non-empty button isn't pressed, then no input
            if(a.buttons[i].keys[k] != SDLK_UNKNOWN && a.buttons[i].isPressed[k] == false)
            {
                isPressed = false;
                break;
            }
        }

        if(isPressed) //Checking if previously pressed is false
        {
            for(int k = 0; k < 3; k++){
                if(a.buttons[i].previouslyPressed[k] == false && a.buttons[i].keys[k] != SDLK_UNKNOWN)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GetActionDownByName(std::string name) //Version with string.
{
    for(int i = 0; i < sizeof(actions) / sizeof(actions[0]); i++){
        if(actions[i].name == name){
            return GetActionDown(actions[i]);
        }
    }
    printf("Couldn't find an input for action named: %s \n",name);
    return false;
}

bool GetActionUp(Action a)
{
    for(int i = 0; i < 2; i++)
    {
        //Checks if there isn't any bindings
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
        
        //Check that if a button isn't pressed
        bool isntPressed = false;
        for(int k = 0; k < 3; k++){
            if(a.buttons[i].keys[k] != SDLK_UNKNOWN && a.buttons[i].isPressed[k] == false){
                isntPressed = true;
                break;
            }
        }

        if(isntPressed)
        {
            //Checking if previously pressed is false
            for(int k = 0; k < 3; k++){
                if(a.buttons[i].previouslyPressed[k] == false && a.buttons[i].keys[k] != SDLK_UNKNOWN){
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool GetActionUpByName(std::string name) //Version with string.
{
    for(int i = 0; i < sizeof(actions) / sizeof(actions[0]); i++){
        if(actions[i].name == name){
            return GetActionUp(actions[i]);
        }
    }
    printf("Couldn't find an input for action named: %s \n",name);
    return false;
}