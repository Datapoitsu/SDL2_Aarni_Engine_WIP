#include <AarniEngine/engine.h>

void Start() //This function is called at the start of the app.
{
    //Play ball
    root->AddChild((*new Transform())); //Ball 1
    dynamic_cast<Transform*>(root->children[0])->position = {512 + ((rand() % 2) * 2 - 1) * (50 + rand() % 200),250, 512 + ((rand() % 2) * 2 - 1) * (50 + rand() % 200)};
    root->children[0]->AddChild(*new Ball());
    dynamic_cast<Ball*>(root->children[0]->children[0])->velocity = {((rand() % 2) * 2 - 1) * (10 + rand() % 15),0, ((rand() % 2) * 2 - 1) * (10 + rand() % 15)};
    
    root->AddChild((*new Transform())); //Ball 2
    dynamic_cast<Transform*>(root->children[1])->position = {512 +((rand() % 2) * 2 - 1) * (50 + rand() % 200),250, 512 + ((rand() % 2) * 2 - 1) * (50 + rand() % 200)};
    root->children[1]->AddChild(*new Ball());
    dynamic_cast<Ball*>(root->children[1]->children[0])->velocity = {((rand() % 2) * 2 - 1) * (10 + rand() % 15),0, ((rand() % 2) * 2 - 1) * (10 + rand() % 15)};
}

void Update() //This function is called at every frame.
{

}