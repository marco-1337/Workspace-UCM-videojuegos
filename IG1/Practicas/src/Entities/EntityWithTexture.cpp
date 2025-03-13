#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "EntityWithTexture.h"

using namespace glm;

// Apartado 19
EntityWithTexture::EntityWithTexture(Texture* texture, GLboolean modulate)
{
	mTexture = texture;
	mModulate = modulate;
    // Habilita que la textura funcione
	mShader = Shader::get("texture");
}
void
EntityWithTexture::render (const glm::mat4& modelViewMat) const 
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", static_cast<bool>(mModulate));
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (mTexture != nullptr) mTexture->bind();
		mMesh->render();
		if (mTexture != nullptr) mTexture->unbind();
	}
}