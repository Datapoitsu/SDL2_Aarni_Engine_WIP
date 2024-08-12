#include <AarniEngine/Engine.h>

Transform camera;
Mesh *m;

void Start() //This function is called at the start of the app.
{
    camera.position = {0,0,-10};
    *m->vertexes = (Vector *)malloc(5*sizeof(Vector));
    Vector v[] = {{0,1,0},{-1,0,-1},{1,0,-1},{-1,0,1},{1,0,1}};
    *m->vertexes = v;

    *m->faces = (Face *)malloc(3*6*sizeof(Vector));
    Face f[] = {{0,2,1},{0,4,2},{0,3,4},{0,1,3},{1,2,3},{4,3,2}};
}

void Update(float deltaTime) //This function is called every frame.
{

}