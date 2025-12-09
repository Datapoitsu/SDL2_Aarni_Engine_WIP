#ifndef _INPUTH_
#define _INPUTH_

#include <SDL2/SDL.h>
#include <string.h>
#include <fstream>
#include <iostream>

const char defaultInputConfigPath[] = "Binding.config";

struct ButtonCombination
{
    //Last scancode is the main one. When repeating a button press, the last scancode needs to be released.
    std::vector<SDL_Scancode> scancodes;
    bool currentlyPressed = false;
    bool previouslyPressed = false;

    ButtonCombination(std::vector<SDL_Scancode> keyName = {})
    {
        scancodes = keyName;
    }

    bool ButtonCombinationPressed()
    {
        return currentlyPressed;        
    }

    bool ButtonCombinationUp()
    {
        return !currentlyPressed && previouslyPressed;
    }

    bool ButtonCombinationDown()
    {
        return currentlyPressed && !previouslyPressed;
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const ButtonCombination& pt); //overriding << operator
};

std::ostream &operator<<(std::ostream &os, const ButtonCombination &b) // overriding << operator
{
    for(int i = 0; i < b.scancodes.capacity(); i++)
    {
        os << b.scancodes[i];
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
            if(ButtonCombinations[i].ButtonCombinationPressed())
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

void UpdateInputs(SDL_Event e) //Checks all defined actions and if the ButtonCombinations are pressed.
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    
    for(int i = 0; i < actions.capacity(); i++)
    {
        for(int k = 0; k < actions[i].ButtonCombinations.capacity(); k++)
        {
            actions[i].ButtonCombinations[k].previouslyPressed = actions[i].ButtonCombinations[k].currentlyPressed;
            if(actions[i].ButtonCombinations[k].scancodes.capacity() == 1)
            {
                actions[i].ButtonCombinations[k].currentlyPressed = 
            }

            for(int j = 0; j < actions[i].ButtonCombinations[k].scancodes.capacity(); j++)
            {
                actions[i].ButtonCombinations[k].currentlyPressed = keyState[];
            }
        }
    }
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

bool GetButtonByName(char buttonName[])
{
    /*if(Event.key.keysym.sym == SDL_GetKeyFromName(buttonName)){
        return true;
    }*/
    return false;
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

                if(buffer[i] == '+')
                {
                    SDL_Keymod mod = SDL_GetModFromName(sub);
                    if (mod != KMOD_NONE)
                    {
                        ButtonCombinationHolder.modification = (SDL_Keymod)(ButtonCombinationHolder.modification | (SDL_GetModFromName(sub)));
                    }
                    ButtonCombinationNameBegin = i + 1;
                }
                else if (buffer[i] == '}')
                {
                    SDL_Keycode key = SDL_GetKeyFromName(sub);
                    if(key != SDLK_UNKNOWN)
                    {
                        ButtonCombinationHolder.key = key;
                    }
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
            file << SDL_GetNamesFromMod(actions[i].ButtonCombinations[k].modification);
            if(actions[i].ButtonCombinations[k].modification != KMOD_NONE)
            {
                file << "+";
            }
            file << SDL_GetKeyName(actions[i].ButtonCombinations[k].key) << "}";
        }
        if(i < actions.capacity() - 1) //No new line for the last row
        {
            file << "\n";
        }
    }
    file.close();
}
#endif