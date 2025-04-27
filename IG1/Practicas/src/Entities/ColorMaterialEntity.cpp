#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "ColorMaterialEntity.h"

using namespace glm;

ColorMaterialEntity::ColorMaterialEntity(glm::dvec4 color) :
EntityWithMaterial()
{
    _normalsShader = Shader::get("normals");

	mMaterial = Material(color);
}

void
ColorMaterialEntity::render(const glm::mat4& modelViewMat) const
{
	if (Abs_Entity::mMesh != nullptr) 
	{
		EntityWithMaterial::render(modelViewMat);

		if (IG1App::s_ig1app.showNormals())
		{
			_normalsShader->use();
			_normalsShader->setUniform("modelView", modelViewMat * mModelMat);
	
			mMesh->render();
		}
	}
}