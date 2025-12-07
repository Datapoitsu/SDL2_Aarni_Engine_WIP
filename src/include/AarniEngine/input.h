#ifndef _INPUTH_
#define _INPUTH_

#include <SDL2/SDL.h>
#include <string.h>

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
    std::cout << "Looking for mod of the " << c << std::endl;
    if (strcmp(c,"") == 0)              { return KMOD_NONE; }
    if (strcmp(c,"Left Shift") == 0)    { return KMOD_LSHIFT ; }
    if (strcmp(c,"Right Shift") == 0)   { return KMOD_RSHIFT; }
    if (strcmp(c,"Shift") == 0)         { return KMOD_SHIFT; }
    if (strcmp(c,"Left Ctrl") == 0)     { return KMOD_LCTRL; }
    if (strcmp(c,"Right Ctrl") == 0)    { return KMOD_RCTRL; }
    if (strcmp(c,"Ctrl") == 0)          { return KMOD_CTRL; }
    if (strcmp(c,"Left Alt") == 0)      { return KMOD_LALT; }
    if (strcmp(c,"Right Alt") == 0)     { return KMOD_RALT; }
    if (strcmp(c,"Alt") == 0)           { return KMOD_ALT; }
    if (strcmp(c,"Left GUI") == 0)      { return KMOD_LGUI; }
    if (strcmp(c,"Right GUI") == 0)     { return KMOD_RGUI; }
    if (strcmp(c,"GUI") == 0)           { return KMOD_GUI; }
    if (strcmp(c,"Num") == 0)           { return KMOD_NUM; }
    if (strcmp(c,"Caps") == 0)          { return KMOD_CAPS; }
    if (strcmp(c,"Mode") == 0)          { return KMOD_MODE; }
    std::cout << "Missing key modifier for name " << c << std::endl;
    return KMOD_NONE;
}

struct Button
{
    //Repeating the button press requires releasing and pressing the main key, modifiers aren't required for repeating.
    SDL_Keycode key;
    bool currentlyPressed = false;
    bool previouslyPressed = false;
    std::vector<SDL_Keymod> modifiers;
    std::vector<bool> modifiersPressedArr;

    Button(SDL_Keycode keyName = SDLK_UNKNOWN, std::vector<SDL_Keymod> modifiersNames = {})
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

    bool ButtonPressed()
    {
        return (currentlyPressed && ModifiersPressed());        
    }

    bool ButtonUp()
    {
        return (!currentlyPressed && previouslyPressed && ModifiersPressed());
    }

    bool ButtonDown()
    {
        return (currentlyPressed && !previouslyPressed && ModifiersPressed());
    }

    // ----- Printing ----- //
    friend std::ostream& operator<<(std::ostream& os, const Button& pt); //overriding << operator
};

std::ostream &operator<<(std::ostream &os, const Button &b) // overriding << operator
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
    std::vector<Button> buttons;

    Action(char actionName[] = (char*)("Undefined"), std::vector<Button> buttonList = {})
    {
        strncpy(name, actionName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';  // ensure null-termination
        buttons = buttonList;
    }

    bool GetAction()
    {
        for(int i = 0; i < buttons.capacity(); i++)
        {
            if(buttons[i].ButtonPressed())
            {
                return true;
            }
        }
        return false;
    }

    bool GetActionDown()
    {
        for(int i = 0; i < buttons.capacity(); i++)
        {
            if(buttons[i].ButtonDown())
            {
                return true;
            }
        }
        return false;
    }

    bool GetActionUp()
    {
        for(int i = 0; i < buttons.capacity(); i++)
        {
            if(buttons[i].ButtonUp())
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
    if (a.buttons.capacity() == 0) //Missing binding.
    {
        os << "\t" << "Unbinded" << std::endl;
        return os;
    }

    for(int i = 0; i < a.buttons.capacity(); i++)
    {
        std::cout << "\t" << a.buttons[i] << std::endl;
    }
    return os;
}

std::vector<Action> actions =
{
    Action((char*)"up", {Button(SDLK_w),Button(SDLK_UP)}),
    Action((char*)"down", {Button(SDLK_s),Button(SDLK_DOWN)}),
    Action((char*)"right", {Button(SDLK_d),Button(SDLK_RIGHT)}),
    Action((char*)"left", {Button(SDLK_a),Button(SDLK_LEFT)}),
    Action((char*)"activate", {Button(SDLK_e)}),
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
    a->buttons.clear();
    a->buttons.shrink_to_fit();
}

void UnbindAll()
{
    for(int i = 0; i < actions.capacity(); i++)
    {
        Unbind(&actions[i]);
    }
}

void UpdateInputs(SDL_Event e) //Checks all defined actions and if the buttons are pressed.
{
    for(int i = 0; i < actions.capacity(); i++)
    {
        for(int k = 0; k < actions[i].buttons.capacity(); k++)
        {
            if (e.key.keysym.sym == actions[i].buttons[k].key)
            {
                if(e.type == SDL_KEYDOWN) //Key pressed down
                {
                    actions[i].buttons[k].currentlyPressed = true;
                }
                if(e.type == SDL_KEYUP) //Key pressed up
                {
                    actions[i].buttons[k].currentlyPressed = true;
                }
            }
        }
        for(int k = 0; k < actions[i].buttons.capacity(); k++)
        {
            for(int j = 0; j < actions[i].buttons[k].modifiers.capacity(); j++)
            {
                if (e.key.keysym.sym == actions[i].buttons[k].modifiers[j])
                {
                    if(e.type == SDL_KEYDOWN) //Key pressed down
                    {
                        actions[i].buttons[k].modifiersPressedArr[j] = true;
                    }
                    if(e.type == SDL_KEYUP) //Key pressed up
                    {
                        actions[i].buttons[k].modifiersPressedArr[j] = true;
                    }
                }
            }
        }
    }
}

void UpdatePreviousInputs(SDL_Event e) //Sets values for previously pressed buttons. Used for GetKeyUp & GetKeyDown.
{
    for(int i = 0; i < actions.capacity(); i++)
    {
        for(int k = 0; k < actions[i].buttons.capacity(); k++)
        {
            actions[i].buttons[k].previouslyPressed = actions[i].buttons[k].currentlyPressed;
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

void ReadInputConfig(char path[] = (char*)"Binding.config")
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
        printf("%s", buffer);

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
        
        std::vector<Button> resultButtons;
        Button buttonHolder;
        int buttonNameBegin = nameLength;
        for(int i = nameLength; i < sizeof(buffer); i++) //Starts from first bracket
        {
            if(buffer[i] == '\0') //Exit once the row ends
            {
                break;
            }
            if(buffer[i] == '{')
            {
                buttonHolder = Button();
                buttonNameBegin = i + 1;
            }
            if(buffer[i] == '+' || buffer[i] == '}')
            {
                std::cout << buttonNameBegin << " " << i << " " << i - buttonNameBegin << std::endl;
                char sub[i - buttonNameBegin + 1];
                strncpy(sub, buffer + buttonNameBegin, i - buttonNameBegin);                
                sub[i - buttonNameBegin] = '\0';
                std::cout << sub << std::endl;

                buttonNameBegin = i + 1;

                if(buffer[i] == '+')
                {
                    std::cout << "Mod: " << SDL_GetModFromName(sub) << std::endl;
                    buttonHolder.modifiers.push_back(SDL_GetModFromName(sub));
                    buttonNameBegin = i + 1;
                }
                else if (buffer[i] == '}')
                {
                    buttonHolder.key = SDL_GetKeyFromName(sub);
                    actions[actionIndex].buttons.push_back(buttonHolder);
                    buttonHolder = Button();
                    buttonNameBegin = i + 1;
                }
            }
        }
    }
    fclose(fptr);
}
#endif