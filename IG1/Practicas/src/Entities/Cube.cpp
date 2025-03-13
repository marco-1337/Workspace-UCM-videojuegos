#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Cube.h"

using namespace glm;

//Apartado 15
Cube::Cube(GLdouble length)
{
	mMesh = Mesh::generateCube(length);
	mColor = {0., 0., 0., 1.};
}

//Apartado 15
void
Cube::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("color", static_cast<glm::vec4>(mColor));
		upload(aMat);
		glEnable(GL_CULL_FACE);

			glCullFace(GL_FRONT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			mMesh->render();

			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			mMesh->render();
		glDisable(GL_CULL_FACE);
	}
}