#include <AarniEngine/engine.h>

Transform camera;
float FovX = 90; //Angle in degrees.
//Planes that camera starts and stops rendering.
float frontPlane = 0.1f;
float backPlane = 100.0f;

GameObject pyramid;

Mesh me;
Mesh *m;

void Start() //This function is called at the start of the app.
{
    
    m = &me;
    camera.position = {0,0,-10};

    *m->vertexes = (Vector *)malloc(5*sizeof(Vector));
    Vector v[] = {{0,1,0},{-1,0,-1},{1,0,-1},{-1,0,1},{1,0,1}};
    *m->vertexes = v;

    *m->faces = (Face *)malloc(3*6*sizeof(Vector));
    Face f[] = {{0,2,1},{0,4,2},{0,3,4},{0,1,3},{1,2,3},{4,3,2}};
    *m->faces = f;

    strcpy(pyramid.name, "Pyramid");
    *pyramid.components = malloc(sizeof(&me));
    
    pyramid.components[0] = &me;

    std::cout << pyramid.name << std::endl;
    std::cout << pyramid.components[0] << std::endl;
}

void Update(float deltaTime) //This function is called every frame.
{

}