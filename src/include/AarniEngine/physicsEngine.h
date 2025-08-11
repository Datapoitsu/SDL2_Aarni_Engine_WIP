#ifndef _PHYSICSENGINEH_
#define _PHYSICSENGINEH_

#include <vector>
#include <AarniEngine/component.h>
#include <AarniEngine/circleCollider.h>

std::vector<Component*> physicsComponents;
std::vector<Transform*> physicsComponentsTransforms;
int physicsComponentCount = 0;

void CalculateCollisions();
void FindPhysicsComponents(Component *c, Transform *t);

void PhysicsEngine()
{
    physicsComponents = {};
    physicsComponentCount = 0;
    FindPhysicsComponents(root, new Transform());
    CalculateCollisions();
}

void CalculateCollisions()
{
    SDL_SetRenderDrawColor(RenderInformation, backgroundColour[0], backgroundColour[1], backgroundColour[2], 255);
    SDL_RenderClear(RenderInformation); //Fills the screen with the background colour
    for(int i = 0; i < physicsComponentCount; i++)
    {
        DrawCircle(physicsComponentsTransforms[i]->position.x, physicsComponentsTransforms[i]->position.y, dynamic_cast<CircleCollider*>(physicsComponents[i])->radius, {255,(Uint8)((255 / physicsComponentCount) * i),(Uint8)(255 - (255 / physicsComponentCount) * i)});
    }
    SDL_RenderPresent(RenderInformation);

    for(int i = 0; i < physicsComponentCount - 1; i++)
    {
        for(int k = i + 1; k < physicsComponentCount; k++)
        {
            // Circle vs Circle.
            if(physicsComponents[i]->componentType == circleCollider2D && physicsComponents[k]->componentType == circleCollider2D)
            {
                float radiuses = dynamic_cast<CircleCollider*>(physicsComponents[i])->radius + dynamic_cast<CircleCollider*>(physicsComponents[k])->radius;
                float x1 = physicsComponentsTransforms[i]->position.x;
                float y1 = physicsComponentsTransforms[i]->position.y;
                Vector2 *v1 = new Vector2(x1,y1);
                Vector2 *v2 = new Vector2(physicsComponentsTransforms[k]->position.x,physicsComponentsTransforms[k]->position.y);
                float distance = Vector2::Distance(*v1,*v2);
                if (distance < radiuses)
                {
                    dynamic_cast<CircleCollider*>(physicsComponents[i])->OnCollisionEnter();
                    dynamic_cast<CircleCollider*>(physicsComponents[k])->OnCollisionEnter();
                }
            }
        }
    }
}

void FindPhysicsComponents(Component *c, Transform *t = new Transform())
{
    Transform *t2 = new Transform();
    t2->position += t->position;

    if(c->componentType == transform)
    {
        t2->position += dynamic_cast<Transform*>(c)->position;
    }
    if(c->componentType == circleCollider2D)
    {
        physicsComponents.push_back(c);
        physicsComponentsTransforms.push_back(t);
        physicsComponentCount++;
    }
    for(int i = 0; i < c->childCount; i++)
    {
        FindPhysicsComponents(c->children[i],t2);
    }
    return;
}
#endif