#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Cone.h"

#include "IndexMesh.h"

using namespace glm;

//Apartado 64
Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples)
: ColorMaterialEntity()
{
    vector<vec2> profile = vector<vec2>();

	GLdouble xDist = (R - r) / nRings; 
    GLdouble yDist = h / nRings;

    for (GLuint i = 0; i < nRings + 1; ++i)
    {
		profile.emplace_back(vec2(r + i * xDist, h/2 - i * yDist));
    }

	mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}