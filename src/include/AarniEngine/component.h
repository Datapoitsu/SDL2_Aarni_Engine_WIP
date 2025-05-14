#ifndef _COMPONENTH_
#define _COMPONENTH_

#include <AarniEngine/Engine.h>

class Component
{
    public:
    virtual void Start(){ std::cout << "Startti ei toimi!" << std::endl; };
    virtual void Update(float deltaTime){ std::cout << "Update ei toimi!" << std::endl; };
    virtual ~Component() = default;
};

#endif