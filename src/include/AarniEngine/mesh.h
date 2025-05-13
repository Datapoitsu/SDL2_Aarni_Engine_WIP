#ifndef _MESHH_
#define _MESHH_
#include <AarniEngine/vector.h>
#include <AarniEngine/transform.h>
#include <vector>

struct Face
{
    Vector3 vertexes[3];
};

struct Mesh
{
    std::vector<Face> faces;
};
 
#endif