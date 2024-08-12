#include <AarniEngine/vector.h>
#include <AarniEngine/transform.h>

struct Face
{
    int index[3];
};

struct Mesh{
    Vector *vertexes[0];
    Face *faces[0];
};