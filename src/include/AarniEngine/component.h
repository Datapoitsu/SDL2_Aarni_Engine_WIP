#ifndef _COMPONENTH_
#define _COMPONENTH_

#include <AarniEngine/Engine.h>

enum ComponentType {
    empty,
    transform,
    renderer,
    camera,
    circleCollider2D,
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
    
    void StartRecursive() //Recursivly Starts all components.
    {
        Start();
        for(int i = 0; i < childCount; i++)
        {
            children[i]->Start();
            children[i]->StartRecursive();
        }
    }

    void UpdateRecursive(double deltaTime) //Recursivly Updates all components.
    {
        Update(deltaTime);
        for(int i = 0; i < childCount; i++)
        {
            children[i]->UpdateRecursive(deltaTime);
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