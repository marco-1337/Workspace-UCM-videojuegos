#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "ColorMaterialEntity.h"

using namespace glm;

GLboolean ColorMaterialEntity::mShowNormals = false;

ColorMaterialEntity::ColorMaterialEntity(glm::dvec4 color) : SingleColorEntity(color)
{
    mShader = Shader::get("simple_light");
    _normalsShader = Shader::get("normals");
}

void
ColorMaterialEntity::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		mShader->use();
		mShader->setUniform("color", static_cast<glm::vec4>(mColor));
		upload(aMat);

		glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mMesh->render();

            // Apartado 61
            if (ColorMaterialEntity::mShowNormals)
            {
                _normalsShader->use();
                _normalsShader->setUniform("modelView", modelViewMat);
        
                mMesh->render();
            }

		glDisable(GL_CULL_FACE);
	}
}