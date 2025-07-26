#include <AarniEngine/engine.h>
#include <AarniEngine/renderer.h>
#include <AarniEngine/transform.h>

void Start() //This function is called at the start of the app.
{
    Root->AddChild((*new Component()));
    Root->children[0]->AddChild((*new Transform()));
    Root->children[0]->AddChild((*new Renderer()));
    dynamic_cast<Renderer*>(Root->children[0]->children[1])->mesh = Mesh::LoadModel("src/Game/Models/Cube.obj");
    dynamic_cast<Renderer*>(Root->children[0]->children[1])->mesh.PrintMeshData();
    std::cout << Root->children[0]->componentType << std::endl;
}

void Update() //This function is called at every frame.
{
    
}