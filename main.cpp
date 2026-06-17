#include <AarniEngine/engine.h>

Sprite s;

void Start() //This function is called at the start of the app.
{
    s.loadSprite("Keys.png");
    s.splicingMethod = Sprite::Splicing::GridByCellSize;
    s.countHor = 16;
    s.countVer = 16;
}

void Update() //This function is called at every frame.
{
    
}