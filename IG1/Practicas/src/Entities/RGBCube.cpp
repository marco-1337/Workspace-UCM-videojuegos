#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "RGBCube.h"

using namespace glm;

//Apartado 16
RGBCube::RGBCube(GLdouble length): _length(length)
{
	mMesh = Mesh::generateRGBCube(length);
	mModelMat = glm::translate(mModelMat, {length/2, length/2, -length/2});
}

//Apartado 16
void
RGBCube::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modelView", aMat);
		upload(aMat);
		glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mMesh->render();
		glDisable(GL_CULL_FACE);
	}
}

// Apartado 17
void 
RGBCube::update()
{
    /*
    Segun en que punto de la rotacion se encuentre la hará en según que ejes

    En todas hace siempre lo mismo, añade las rotaciones completas previas sobre la identidad (baseMat),
    después lo rota y lo traslada siempre a la misma posicion que es la posicion de origen.
    */

	if (_rotaciones.x < glm::pi<GLfloat>())
	{
		_rotaciones.x = clamp<GLfloat>(_rotaciones.x + 0.04, 0.0, glm::pi<GLfloat>());
		mModelMat = glm::rotate(mBaseMat, _rotaciones.x, glm::vec3(1, 0, 0));
		mModelMat = glm::translate(mModelMat, {_length/2, _length/2, -_length/2});
	}
	else if (_rotaciones.z < glm::pi<GLfloat>())
	{
		mModelMat = glm::rotate(mBaseMat, glm::pi<GLfloat>(), glm::vec3(1, 0, 0));

		_rotaciones.z = clamp<GLfloat>(_rotaciones.z + 0.04, 0.0, glm::pi<GLfloat>());
		mModelMat = glm::rotate(mModelMat, _rotaciones.z, glm::vec3(0, 0, -1));
		mModelMat = glm::translate(mModelMat, {_length/2, _length/2, -_length/2});
	}
	else if (_rotaciones.y < glm::pi<GLfloat>())
	{
		mModelMat = glm::rotate(mBaseMat, glm::pi<GLfloat>(), glm::vec3(1, 0, 0));
		mModelMat = glm::rotate(mModelMat, glm::pi<GLfloat>(), glm::vec3(0, 0, -1));

		_rotaciones.y = clamp<GLfloat>(_rotaciones.y + 0.04, 0.0, glm::pi<GLfloat>());
		mModelMat = glm::rotate(mModelMat, _rotaciones.y, glm::vec3(0, 1, 0));
		mModelMat = glm::translate(mModelMat, {_length/2, _length/2, -_length/2});
	}
	else 
		_rotaciones = {0., 0., 0.};
}