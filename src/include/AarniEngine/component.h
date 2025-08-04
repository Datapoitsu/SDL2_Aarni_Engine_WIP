#ifndef _COMPONENTH_
#define _COMPONENTH_

#include <AarniEngine/Engine.h>

enum ComponentType {
    empty,
    transform,
    renderer,
    camera,
    ball,
};

class Component
{
    public:
        virtual void Start(){};
        virtual void Update(double deltaTime){};
        virtual void Reset(){};
        virtual ~Component() = default;
        int childCount = 0;
        std::vector<Component*> children;
        Component *parent = nullptr;
        
        enum ComponentType componentType = empty;
    
    void StartChildren() //Recursivly Starts all components.
    {
        for(int i = 0; i < childCount; i++)
        {
            children[i]->Start();
            children[i]->StartChildren();
        }
    }

    void UpdateChildren(double deltaTime) //Recursivly Updates all components.
    {
        for(int i = 0; i < childCount; i++)
        {
            children[i]->Update(deltaTime);
            children[i]->UpdateChildren(deltaTime);
        }
    }

    void AddChild(Component& child)
    {
        child.parent = this;
        children.push_back(&child);
        childCount++;
    }
};

#endif