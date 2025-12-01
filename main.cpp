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
    root->AddChild(*new Transform());
    dynamic_cast<Transform*>(root->children[0])->position = {500,500,0};    
    root->children[0]->AddChild(*new CircleCollider());
    dynamic_cast<CircleCollider*>(root->children[0]->children[0])->radius = 25;

    root->AddChild(*new Transform());
    dynamic_cast<Transform*>(root->children[1])->position = {500,600,0};    
    root->children[1]->AddChild(*new CircleCollider());
    dynamic_cast<CircleCollider*>(root->children[1]->children[0])->radius = 25;

    root->AddChild(*new Transform());
    dynamic_cast<Transform*>(root->children[2])->position = {700,600,0};    
    root->children[2]->AddChild(*new CircleCollider());
    dynamic_cast<CircleCollider*>(root->children[2]->children[0])->radius = 50;

    for(int i = 0; i < 10; i++)
    {
        CreateBall();
    }
}

void Update() //This function is called at every frame.
{

}