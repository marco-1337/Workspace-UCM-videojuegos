#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "WingAdvancedTIE.h"

using namespace glm;

WingAdvancedTIE::WingAdvancedTIE(GLdouble height, GLdouble width, GLdouble wingOffset, 
    Texture* texture, GLboolean modulate)
: TranslucentEntity(texture, modulate)
{
	mMesh = Mesh::generateTIEWing(height, width, wingOffset);
}