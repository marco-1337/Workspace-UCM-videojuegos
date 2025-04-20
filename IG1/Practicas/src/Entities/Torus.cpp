#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Torus.h"
#include "IndexMesh.h"

using namespace glm;

//Apartado 56
Torus::Torus(glm::dvec4 color, GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples)
: ColorMaterialEntity(color)
{
    vector<vec2> profile = vector<vec2>();

    GLdouble angleStep = radians(360.0) / nPoints;

    // clockwise para culling bien
    GLdouble theta = -(2.0f * std::numbers::pi) / nPoints;

    for (GLuint i = 0; i < nPoints + 1; ++i)
    {
        profile.emplace_back(R + (r * cos(theta * i)), r * sin(theta * i));
    }

    mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}