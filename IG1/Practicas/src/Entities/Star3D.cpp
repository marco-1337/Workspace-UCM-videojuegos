#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Star3D.h"

using namespace glm;

// Apartado 27
Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, Texture* texture, GLboolean modulate)
: EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
}
void Star3D::render(const glm::mat4& modelViewMat) const 
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

		aMat = modelViewMat * glm::scale(mModelMat, glm::vec3(1, 1, -1)); // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (mTexture != nullptr) mTexture->bind();
		mMesh->render();
		if (mTexture != nullptr) mTexture->unbind();
	}
}

// Apartado 28
// COMENTAR
void Star3D::update()
{
	mModelMat = glm::rotate(mBaseMat, _yRotation += ROTATION_SPEED, glm::vec3(0, 1, 0));
	mModelMat = glm::rotate(mModelMat, _zRotation += ROTATION_SPEED, glm::vec3(0, 0, 1));
}