#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "SingleColorEntity.h"

using namespace glm;

// Apartado 3
SingleColorEntity::SingleColorEntity(glm::dvec4 color): mColor(color)
{
	mShader = Shader::get("simple");
}

glm::dvec4 
SingleColorEntity::color() const { return mColor; }

void
SingleColorEntity::setColor(glm::dvec4 color) 
{
	mColor = color; 
}

void
SingleColorEntity::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("color", static_cast<glm::vec4>(mColor));
		upload(aMat);
		mMesh->render();
	}
}
// !Apartado 3
