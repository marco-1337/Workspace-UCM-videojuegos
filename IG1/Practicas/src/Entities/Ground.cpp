#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Ground.h"

using namespace glm;

// Apartado 18
Ground::Ground(GLdouble w, GLdouble h, Texture* texture, GLboolean modulate, GLint rw, GLint rh)
: EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateRectangleTexCor(w, h, rw, rh);
}
