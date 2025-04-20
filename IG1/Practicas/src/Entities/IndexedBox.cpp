#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "IndexedBox.h"

#include "IndexMesh.h"

using namespace glm;

//Apartado 60
IndexedBox::IndexedBox(GLdouble length)
: ColorMaterialEntity({0., 1., 0., 1.})
{
	mMesh = IndexMesh::generateIndexedBox(length);
}