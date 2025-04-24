#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Sphere.h"

#include "IndexMesh.h"

using namespace glm;

//Apartado 64
Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians)
: ColorMaterialEntity()
{
	mMesh = IndexMesh::generateIndexedSphere(radius, nParallels, nMeridians);
}