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
    mMesh = IndexMesh::generateIndexedTorus(R, r, nPoints, nSamples);
}