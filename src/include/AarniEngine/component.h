#ifndef _COMPONENTH_
#define _COMPONENTH_

#include <AarniEngine/Engine.h>

class Component
{
    public:
        virtual void Start(){};
        virtual void Update(){};
        virtual void Reset(){};
        virtual ~Component() = default;
};

#endif