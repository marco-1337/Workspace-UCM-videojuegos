#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "RegularPolygon.h"

using namespace glm;
 
// Apartado 4
RegularPolygon::RegularPolygon(GLuint num, GLdouble r, glm::dvec4 color): SingleColorEntity(color)
{
	mMesh = Mesh::generateRegularPolygon(num, r);
}