#include <AarniEngine/engine.h>

void Start() //This function is called at the start of the app.
{
    root->AddChild(*new Transform()); //P1
    dynamic_cast<Transform*>(root->children[0])->scale = {5,100,1};
    dynamic_cast<Transform*>(root->children[0])->position = {50,screenHeigth / 2,0};
    root->children[0]->AddChild(*new Renderer2D());
    dynamic_cast<Renderer2D*>(root->children[0]->children[0])->sprite = IMG_LoadTexture(RenderInformation,"src/Game/Sprites/square.png");
    dynamic_cast<Renderer2D*>(root->children[0]->children[0])->anchor = Renderer2D::AnchorPosition::middleCenter;
    dynamic_cast<Renderer2D*>(root->children[0]->children[0])->colour = {255,0,0};
    root->children[0]->AddChild(*new Player());
    dynamic_cast<Player*>(root->children[0]->children[1])->upInput = "Up1";
    dynamic_cast<Player*>(root->children[0]->children[1])->downInput = "Down1";

    root->AddChild(*new Transform()); //P2
    dynamic_cast<Transform*>(root->children[1])->position = {screenWidth - 50, screenHeigth / 2,0};
    dynamic_cast<Transform*>(root->children[1])->scale = {5,100,1};
    root->children[1]->AddChild(*new Renderer2D());
    dynamic_cast<Renderer2D*>(root->children[1]->children[0])->sprite = IMG_LoadTexture(RenderInformation,"src/Game/Sprites/square.png");
    dynamic_cast<Renderer2D*>(root->children[1]->children[0])->anchor = Renderer2D::AnchorPosition::middleCenter;
    dynamic_cast<Renderer2D*>(root->children[1]->children[0])->colour = {0,0,255};
    root->children[1]->AddChild(*new Player());
    dynamic_cast<Player*>(root->children[1]->children[1])->upInput = "Up2";
    dynamic_cast<Player*>(root->children[1]->children[1])->downInput = "Down2";

    root->AddChild(*new Transform()); //Ball
    dynamic_cast<Transform*>(root->children[2])->position = {screenWidth /2, screenHeigth / 2,0};
    dynamic_cast<Transform*>(root->children[2])->scale = {32, 32,0};
    root->children[2]->AddChild(*new Ball());
}

void Update() //This function is called at every frame.
{

}