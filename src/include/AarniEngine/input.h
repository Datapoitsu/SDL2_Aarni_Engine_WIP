#ifndef _INPUTH_
#define _INPUTH_

#include <SDL2/SDL.h>
#include <string.h>
#include <fstream>
#include <iostream>

char defaultInputConfigPath[] = "Binding.config";

const char* SDL_GetNameFromMod(SDL_Keymod mod)
{
    if (mod == KMOD_NONE)   { return ""; }
    if (mod == KMOD_LSHIFT) { return "Left Shift"; }
    if (mod == KMOD_RSHIFT) { return "Right Shift"; }
    if (mod == KMOD_SHIFT)  { return "Shift"; }
    if (mod == KMOD_LCTRL)  { return "Left Ctrl"; }
    if (mod == KMOD_RCTRL)  { return "Right Ctrl"; }
    if (mod == KMOD_CTRL)   { return "Ctrl"; }
    if (mod == KMOD_LALT)   { return "Left Alt"; }
    if (mod == KMOD_RALT)   { return "Right Alt"; }
    if (mod == KMOD_ALT)    { return "Alt"; }
    if (mod == KMOD_LGUI)   { return "Left GUI"; }
    if (mod == KMOD_RGUI)   { return "Right GUI"; }
    if (mod == KMOD_GUI)    { return "GUI"; }
    if (mod == KMOD_NUM)    { return "Num"; }
    if (mod == KMOD_CAPS)   { return "Caps"; }
    if (mod == KMOD_MODE)   { return "Mode"; }
    std::cout << "Missing name for key modifier " << mod << std::endl;
    return "None";
}

const SDL_Keymod SDL_GetModFromName(char c[])
{
    //Lower case.
    for(int i = 0; i < sizeof(*c) / sizeof(char); i++)
    {
        c[i] = (char)tolower(c[i]);
    }
    if (strcmp(c,"") == 0)              { return KMOD_NONE; }
    if (strcmp(c,"left shift") == 0)    { return KMOD_LSHIFT ; }
    if (strcmp(c,"right shift") == 0)   { return KMOD_RSHIFT; }
    if (strcmp(c,"shift") == 0)         { return KMOD_SHIFT; }
    if (strcmp(c,"left ctrl") == 0)     { return KMOD_LCTRL; }
    if (strcmp(c,"right ctrl") == 0)    { return KMOD_RCTRL; }
    if (strcmp(c,"ctrl") == 0)          { return KMOD_CTRL; }
    if (strcmp(c,"left alt") == 0)      { return KMOD_LALT; }
    if (strcmp(c,"right alt") == 0)     { return KMOD_RALT; }
    if (strcmp(c,"alt") == 0)           { return KMOD_ALT; }
    if (strcmp(c,"left gui") == 0)      { return KMOD_LGUI; }
    if (strcmp(c,"right gui") == 0)     { return KMOD_RGUI; }
    if (strcmp(c,"gui") == 0)           { return KMOD_GUI; }
    if (strcmp(c,"num") == 0)           { return KMOD_NUM; }
    if (strcmp(c,"caps") == 0)          { return KMOD_CAPS; }
    if (strcmp(c,"mode") == 0)          { return KMOD_MODE; }
    std::cout << "Missing key modifier for name " << c << std::endl;
    return KMOD_NONE;
}

struct ButtonCombination
{
    //Repeating the ButtonCombination press requires releasing and pressing the main key, modifiers aren't required for repeating.
    SDL_Keycode key;
    bool currentlyPressed = false;
    bool previouslyPressed = false;
    std::vector<SDL_Keymod> modifiers;
    std::vector<bool> modifiersPressedArr;

    ButtonCombination(SDL_Keycode keyName = SDLK_UNKNOWN, std::vector<SDL_Keymod> modifiersNames = {})
    {
        key = keyName;
        modifiers = modifiersNames;
        modifiersPressedArr.assign(modifiersNames.capacity(),false);
    }

    bool ModifiersPressed()
    {
        for(int i = 0; i < modifiersPressedArr.capacity(); i++)
        {
            if(!modifiersPressedArr[i])
            {
                return false;
            }
        }
        return true;
    }

    bool ButtonCombinationPressed()
    {
        return (currentlyPressed && ModifiersPressed());        
    }

    bool ButtonCombinationUp()
    {
        return (!currentlyPressed && previouslyPressed && ModifiersPressed());
    }

    bool ButtonCombinationDown()
    {
        return (currentlyPressed && !previouslyPressed && ModifiersPressed());
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const ButtonCombination& pt); //overriding << operator
};

std::ostream &operator<<(std::ostream &os, const ButtonCombination &b) // overriding << operator
{
    for(int k = 0; k < b.modifiers.capacity(); k++)
    {
        os << SDL_GetNameFromMod(b.modifiers[k]) << " + ";
    }
    os << SDL_GetKeyName(b.key);
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
    Action((char*)"up", {ButtonCombination(SDLK_w),ButtonCombination(SDLK_UP)}),
    Action((char*)"down", {ButtonCombination(SDLK_s),ButtonCombination(SDLK_DOWN)}),
    Action((char*)"right", {ButtonCombination(SDLK_d),ButtonCombination(SDLK_RIGHT)}),
    Action((char*)"left", {ButtonCombination(SDLK_a),ButtonCombination(SDLK_LEFT)}),
    Action((char*)"activate", {ButtonCombination(SDLK_e)}),
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
    for(int i = 0; i < actions.capacity(); i++)
    {
        for(int k = 0; k < actions[i].ButtonCombinations.capacity(); k++)
        {
            // ----- Set modifiers ----- //
            for(int j = 0; j < actions[i].ButtonCombinations[k].modifiers.capacity(); j++)
            {
                //std::cout << actions[i].ButtonCombinations[k].modifiers[j] << std::endl;
                std::cout << (e.key.keysym.mod == actions[i].ButtonCombinations[k].modifiers[j]) << std::endl;
            }
            // ----- Set key ----- //
            actions[i].ButtonCombinations[k].previouslyPressed = actions[i].ButtonCombinations[k].currentlyPressed;
            actions[i].ButtonCombinations[k].currentlyPressed = (e.key.keysym.sym == actions[i].ButtonCombinations[k].key);
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
                        ButtonCombinationHolder.modifiers.push_back(SDL_GetModFromName(sub));
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
            for(int j = 0; j < actions[i].ButtonCombinations[k].modifiers.capacity(); j++)
            {
                file << SDL_GetNameFromMod(actions[i].ButtonCombinations[k].modifiers[j]) << "+";
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