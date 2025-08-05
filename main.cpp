#include <AarniEngine/engine.h>

void CreateBall()
{
    root->AddChild((*new Transform())); //Ball 1
    dynamic_cast<Transform*>(root->children[root->childCount - 1])->position = {512 + ((rand() % 2) * 2 - 1) * (50 + rand() % 206),250, 256 + ((rand() % 2) * 2 - 1) * (50 + rand() % 78)};
    root->children[root->childCount - 1]->AddChild(*new Ball());
    Vector3 velocity = *new Vector3((rand() % 2) * 2 - 1,0,(rand() % 2) * 2 - 1 );
    velocity = Vector3::Normalize(velocity);
    velocity *= 25;

    dynamic_cast<Ball*>(root->children[root->childCount - 1]->children[0])->velocity = velocity;
    
}

void Start() //This function is called at the start of the app.
{
    for(int i = 0; i < 100; i++)
    {
        CreateBall();
    }
}

void Update() //This function is called at every frame.
{

}