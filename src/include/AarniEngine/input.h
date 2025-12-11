#ifndef _INPUTH_
#define _INPUTH_

/*
TODO:
Rebind functions
Axis
    GetDelta()
    Deadzone
    Smooth
    Raw

Devices:
    Mouse
        GetPointerPosition()
        GetDelta()
    Controller
        rumble
*/

#include <SDL2/SDL.h>
#include <string.h>
#include <fstream>
#include <iostream>

const char defaultInputConfigPath[] = "Binding.config";
const Uint8 *keyState = SDL_GetKeyboardState(NULL);
Uint8 prevKeys[SDL_NUM_SCANCODES];

struct ButtonCombination
{
    std::vector<SDL_Scancode> scancodes;

    ButtonCombination(std::vector<SDL_Scancode> keyName = {})
    {
        scancodes = keyName;
    }

    bool CurrentlyPressed()
    {
        bool pressed = true;
        for(int i = 0; i < scancodes.capacity(); i++)
        {
            if(!keyState[scancodes[i]])
            {
                pressed = false;
                break;
            }
        }
        return pressed;        
    }

    bool PreviouslyPressed()
    {
        bool pressed = true;
        for(int i = 0; i < scancodes.capacity(); i++)
        {
            if(!prevKeys[scancodes[i]])
            {
                pressed = false;
                break;
            }
        }
        return pressed;        
    }

    bool ButtonCombinationUp()
    {
        return !CurrentlyPressed() && PreviouslyPressed();
    }

    bool ButtonCombinationDown()
    {
        return CurrentlyPressed() && !PreviouslyPressed();
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const ButtonCombination& pt); //overriding << operator
};

std::ostream &operator<<(std::ostream &os, const ButtonCombination &b) // overriding << operator
{
    for(int i = 0; i < b.scancodes.capacity(); i++)
    {
        os << SDL_GetKeyName(SDL_GetKeyFromScancode(b.scancodes[i]));
        if(i < b.scancodes.capacity() - 1)
        {
            os << "+";
        }
    }
    return os;
}

struct Action //Action is something that you would see in binding settings as an action.
{
    public:
    char name[16];
    std::vector<ButtonCombination> ButtonCombinations;

    Action(char actionName[] = (char*)("Undefined"), std::vector<ButtonCombination> ButtonCombinationList = {})
    {
        strncpy(name, actionName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';  // ensure null-termination
        ButtonCombinations = ButtonCombinationList;
    }

    bool GetAction()
    {
        for(int i = 0; i < ButtonCombinations.capacity(); i++)
        {
            if(ButtonCombinations[i].CurrentlyPressed())
            {
                return true;
            }
        }
        return false;
    }

    bool GetActionDown()
    {
        for(int i = 0; i < ButtonCombinations.capacity(); i++)
        {
            if(ButtonCombinations[i].ButtonCombinationDown())
            {
                return true;
            }
        }
        return false;
    }

    bool GetActionUp()
    {
        for(int i = 0; i < ButtonCombinations.capacity(); i++)
        {
            if(ButtonCombinations[i].ButtonCombinationUp())
            {
                return true;
            }
        }
        return false;
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const Action& pt); //overriding << operator
};

std::ostream &operator<<(std::ostream &os, const Action &a) // overriding << operator
{
    os << a.name << ":" << std::endl;
    if (a.ButtonCombinations.capacity() == 0) //Missing binding.
    {
        os << "\t" << "Unbinded" << std::endl;
        return os;
    }

    for(int i = 0; i < a.ButtonCombinations.capacity(); i++)
    {
        std::cout << "\t" << a.ButtonCombinations[i] << std::endl;
    }
    return os;
}

std::vector<Action> actions =
{
    Action((char*)"up",{ButtonCombination({SDL_SCANCODE_W}), ButtonCombination({SDL_SCANCODE_UP})}),
    Action((char*)"down",{ButtonCombination({SDL_SCANCODE_S}), ButtonCombination({SDL_SCANCODE_DOWN})}),
    Action((char*)"right",{ButtonCombination({SDL_SCANCODE_D}), ButtonCombination({SDL_SCANCODE_RIGHT})}),
    Action((char*)"left",{ButtonCombination({SDL_SCANCODE_A}), ButtonCombination({SDL_SCANCODE_LEFT})}),
    Action((char*)"activate",{ButtonCombination({SDL_SCANCODE_LCTRL,SDL_SCANCODE_LSHIFT,SDL_SCANCODE_E})}),
    Action((char*)"crouch",{ButtonCombination({SDL_SCANCODE_LALT})}),
};

void PrintAllActions()
{
    std::cout << "## ----- All Action Inputs ----- ##" << std::endl;
    for(int i = 0; i < actions.capacity(); i++)
    {
        std::cout << actions[i];
    }
}

void Unbind(Action *a)
{
    a->ButtonCombinations.clear();
    a->ButtonCombinations.shrink_to_fit();
}

void UnbindAll()
{
    for(int i = 0; i < actions.capacity(); i++)
    {
        Unbind(&actions[i]);
    }
}

void UpdateInputs() //Checks all defined actions and if the ButtonCombinations are pressed.
{
    SDL_PumpEvents();
    keyState = SDL_GetKeyboardState(NULL);
}

void UpdatePreviousInputs()
{
    memcpy(prevKeys, keyState, SDL_NUM_SCANCODES);
}

bool GetActionByName(std::string name)
{
    //Checks through all actions to find the correct action.
    for(int i = 0; i < actions.capacity(); i++)
    {
        if(actions[i].name == name)
        {
            return actions[i].GetAction();
        }
    }
    std::cout << "Action " << name << " not found" << std::endl;
    return false;
};

bool GetActionDownByName(std::string name)
{
    //Checks through all actions to find the correct action.
    for(int i = 0; i < actions.capacity(); i++)
    {
        if(actions[i].name == name)
        {
            return actions[i].GetActionDown();
        }
    }
    std::cout << "Action " << name << " not found" << std::endl;
    return false;
}

bool GetActionUpByName(std::string name)
{
    //Checks through all actions to find the correct action.
    for(int i = 0; i < actions.capacity(); i++)
    {
        if(actions[i].name == name)
        {
            return actions[i].GetActionUp();
        }
    }
    std::cout << "Action " << name << " not found" << std::endl;
    return false;
}

bool GetButtonByName(const char buttonName[])
{
    return keyState[SDL_GetScancodeFromName(buttonName)];
}

bool GetButtonByName(const std::string *buttonName)
{
    int n = buttonName->length();
    char arr[n + 1];
    strcpy(arr, buttonName->c_str());
    return GetButtonByName(arr);
}

bool GetButtonDownByName(const char buttonName[])
{
    return (!(bool)prevKeys[SDL_GetScancodeFromName(buttonName)] && (bool)keyState[SDL_GetScancodeFromName(buttonName)]);
}

bool GetButtonDownByName(const std::string *buttonName)
{
    int n = buttonName->length();
    char arr[n + 1];
    strcpy(arr, buttonName->c_str());
    return GetButtonDownByName(arr);
}

bool GetButtonUpByName(const char buttonName[])
{
    return ((bool)prevKeys[SDL_GetScancodeFromName(buttonName)] && !(bool)keyState[SDL_GetScancodeFromName(buttonName)]);
}

bool GetButtonUpByName(const std::string *buttonName)
{
    int n = buttonName->length();
    char arr[n + 1];
    strcpy(arr, buttonName->c_str());
    return GetButtonUpByName(arr);
}

void PrintControllers()
{
    std::cout << "# ----- Controllers ----- #" << std::endl;
    std::cout << "Count: " << SDL_NumJoysticks() << std::endl;
    for(int i = 0; i < SDL_NumJoysticks(); i++)
    {
        PrintController(i);
    }
}

void PrintController(int controllerID)
{
    SDL_Joystick *joy = SDL_JoystickOpen(controllerID);
    std::cout << "Controller: " << (controllerID+1) << std::endl;
    std::cout << "\t" << "Name: " << SDL_JoystickName(joy) << std::endl;
    std::cout << "\t" << "Instance ID: " << SDL_JoystickFromInstanceID(controllerID) << std::endl;
    std::cout << "\t" << "Player ID: " << SDL_JoystickFromPlayerIndex(controllerID) << std::endl;
    std::cout << "\t" << "Power: " << SDL_JoystickCurrentPowerLevel(joy) << std::endl;
    std::cout << "\t" << "Type: " << SDL_JoystickGetType(joy) << std::endl;
    std::cout << "\t" << "Vendor: " << SDL_JoystickGetDeviceVendor(controllerID) << std::endl;
    std::cout << "\t" << "Led: " << (bool)SDL_JoystickHasLED(joy) << std::endl;
    std::cout << "\t" << "Rumble: " << (bool)SDL_JoystickHasRumble(joy) << std::endl;
    std::cout << "\t" << "Rumble triggers: " << (bool)SDL_JoystickHasRumbleTriggers(joy) << std::endl;
}

void ReadInputConfig(char path[] = (char*)defaultInputConfigPath)
{
    FILE *fptr = fopen(path, "r");
    if(fptr == NULL)
    {
        std::cout << "Error: File " << path << " is missing!" << std::endl;
        fclose(fptr); 
        return;
    }

    UnbindAll(); //Clears old bindings for the next one
    
    const int bufferSize = 100;
    char buffer[bufferSize];

    while(fgets(buffer, bufferSize, fptr)) // Read the content and print it.
    {
        // ----- Finding the action corresponding to the name ----- //
        int nameLength = 0;
        for(int i = 0; i < bufferSize; i++)
        {
            if(buffer[i] == '{')
            {
                break;
            }
            nameLength++;
        }
        int actionIndex = -1;
        for(int i = 0; i < actions.capacity(); i++)
        {
            for(int k = 0; k < nameLength; k++) //Loop action name
            {
                if(actions[i].name[k] != buffer[k])
                {
                    break;
                }
                if(k == nameLength - 1) //Action found!
                {
                    actionIndex = i;
                }
            }
            if(actionIndex != -1)
            {
                break;
            }
        }
        if(actionIndex == -1) //No action found!
        {
            continue;
        }
        
        std::vector<ButtonCombination> resultButtonCombinations;
        ButtonCombination ButtonCombinationHolder;
        int ButtonCombinationNameBegin = nameLength;
        for(int i = nameLength; i < sizeof(buffer); i++) //Starts from first bracket
        {
            if(buffer[i] == '\0') //Exit once the row ends
            {
                break;
            }
            if(buffer[i] == '{')
            {
                ButtonCombinationHolder = ButtonCombination();
                ButtonCombinationNameBegin = i + 1;
            }
            if(buffer[i] == '+' || buffer[i] == '}')
            {
                char sub[i - ButtonCombinationNameBegin + 1];
                strncpy(sub, buffer + ButtonCombinationNameBegin, i - ButtonCombinationNameBegin);                
                sub[i - ButtonCombinationNameBegin] = '\0';
                ButtonCombinationNameBegin = i + 1;

                if(buffer[i] == '+' or buffer[i] == '}')
                {
                    ButtonCombinationHolder.scancodes.push_back(SDL_GetScancodeFromName(sub));
                    ButtonCombinationNameBegin = i + 1;
                }
                if (buffer[i] == '}')
                {
                    actions[actionIndex].ButtonCombinations.push_back(ButtonCombinationHolder);
                    ButtonCombinationHolder = ButtonCombination();
                    ButtonCombinationNameBegin = i + 1;
                }
            }
        }
    }
    fclose(fptr);
}

void SaveInputConfig(const char *path = defaultInputConfigPath)
{
    std::ofstream file(path);
    if (!file)
    {
        std::cout << "Error: Input safe file not created at SaveInputConfig()" << std::endl;
        return;
    }

    for(int i = 0; i < actions.capacity(); i++)
    {
        file << actions[i].name;
        for(int k = 0; k < actions[i].ButtonCombinations.capacity(); k++)
        {
            file << "{";
            for(int j = 0; j < actions[i].ButtonCombinations[k].scancodes.capacity(); j++)
            {
                file << SDL_GetKeyName(SDL_GetKeyFromScancode(actions[i].ButtonCombinations[k].scancodes[j]));
                if(j < actions[i].ButtonCombinations[k].scancodes.capacity() - 1)
                {
                    file << "+";
                }
            }
            file << "}";
        }
        if(i < actions.capacity() - 1) //No new line for the last row
        {
            file << "\n";
        }
    }
    file.close();
}
#endif