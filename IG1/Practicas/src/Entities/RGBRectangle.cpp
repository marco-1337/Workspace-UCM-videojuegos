#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "RGBRectangle.h"

using namespace glm;

// Apartado 8
RGBRectangle::RGBRectangle(GLdouble w, GLdouble h): EntityWithColors()
{
	mMesh = Mesh::generateRGBRectangle(w, h);
}

// Apartado 8
void
RGBRectangle::render(const glm::mat4& modelViewMat) const
{

    // Igual que el render de RGB Triangle

	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modelView", aMat);
		upload(aMat);
		glEnable(GL_CULL_FACE);

			glCullFace(GL_FRONT);
			//glPointSize(5.);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//glPointSize(1.);
			mMesh->render();

			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			mMesh->render();

		glDisable(GL_CULL_FACE);
	}
}