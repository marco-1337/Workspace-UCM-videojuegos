#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "RGBTriangle.h"

using namespace glm;
 
// Apartado 6
RGBTriangle::RGBTriangle(GLdouble r)
: EntityWithColors()
{
	mMesh = Mesh::generateRGBTriangle(r);
}

// Apartado 7
void
RGBTriangle::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modelView", aMat);
		upload(aMat);

        // La idea general es hacer culling de una cara, renderizar la cara que no se oculta con el modo
        // requerido y hacer lo mismo con la otra cara

		glEnable(GL_CULL_FACE);

			glCullFace(GL_FRONT);
			//glPointSize(5.);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//glPointSize(1.);
			mMesh->render();

			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mMesh->render();

		glDisable(GL_CULL_FACE);
	}
}

// Apartado 13
void 
RGBTriangle::update()
{
	glm::vec3 posOriginal = {mModelMat[3].x, mModelMat[3].y, mModelMat[3].z};
	GLdouble modulo = length(posOriginal);
	GLdouble anguloT = atan2(posOriginal.y, posOriginal.x) + glm::radians(1.0f);
	glm::vec3 posNueva = glm::vec3(modulo*glm::cos(anguloT), modulo*glm::sin(anguloT), 0.0f);

	_anguloRotacion += 0.1;

	mModelMat = glm::translate(mBaseMat, posNueva);
	mModelMat = glm::rotate(mModelMat, _anguloRotacion, glm::vec3(0, 0, -1));
}
