#include <AarniEngine/engine.h>


Transform t = Transform();
SpriteRenderer sr = SpriteRenderer();
Sprite s = Sprite();

void Start() //This function is called at the start of the app.
{
    s.loadSprite("Keys.png");
    s.splicingMethod = Sprite::Splicing::GridByCellSize;
    s.countHor = 16;
    s.countVer = 16;
    t.AddChild(sr);
    root->AddChild(t);
    
    
    
}

void Update() //This function is called at every frame.
{

}


void Start(){}
void Update(){}