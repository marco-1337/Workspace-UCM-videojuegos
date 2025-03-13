#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "BoxOutline.h"

using namespace glm;

// Apartado 23
BoxOutline::BoxOutline(GLdouble length, Texture* texture, Texture* inwardsTexture, GLboolean modulate)
: EntityWithTexture(texture, modulate), mInwardsTexture(inwardsTexture)
{
	mMesh = Mesh::generateBoxOutlineTextCor(length);
}

// Apartado 25
void
BoxOutline::render (const glm::mat4& modelViewMat) const 
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", static_cast<bool>(mModulate));
		upload(aMat);

        // Hace culling y renderiza habilitando por cada cara la textura correspondiente
        
		glEnable(GL_CULL_FACE);

			glCullFace(GL_FRONT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mTexture != nullptr) mTexture->bind();
			mMesh->render();
			if (mTexture != nullptr) mTexture->unbind();

			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mInwardsTexture != nullptr) mInwardsTexture->bind();
			if (mInwardsTexture != nullptr) mMesh->render();
			if (mInwardsTexture != nullptr) mInwardsTexture->unbind();
		
		glDisable(GL_CULL_FACE);
	}
}