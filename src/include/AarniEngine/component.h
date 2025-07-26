#ifndef _COMPONENTH_
#define _COMPONENTH_

#include <AarniEngine/Engine.h>

enum ComponentType {
    empty,
    transform,
    renderer,
};

class Component
{
    public:
        virtual void Start(){};
        virtual void Update(){};
        virtual void Reset(){};
        virtual ~Component() = default;
        int childCount = 0;
        std::vector<Component*> children;
        
        enum ComponentType componentType = empty;
    
    void StartChildren() //Recursivly Starts all components.
    {
        for(int i = 0; i < childCount; i++)
        {
            children[i]->Start();
            children[i]->StartChildren();
        }
    }

    void UpdateChildren() //Recursivly Updates all components.
    {
        for(int i = 0; i < childCount; i++)
        {
            children[i]->Update();
            children[i]->UpdateChildren();
        }
    }

    void AddChild(Component& child)
    {
        children.push_back(&child);
        childCount++;
    }
};

#endif