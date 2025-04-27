#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Disk.h"

#include "IndexMesh.h"

using namespace glm;

//Apartado 64
Disk::Disk(glm::dvec4 color, GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples)
: ColorMaterialEntity(color)
{
    vector<vec2> profile = vector<vec2>();

	GLdouble distance = (R - r) / nRings; 

    for (GLuint i = 0; i < nRings + 1; ++i)
    {
		profile.emplace_back(vec2(r + i * distance, 0));
    }

	mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}