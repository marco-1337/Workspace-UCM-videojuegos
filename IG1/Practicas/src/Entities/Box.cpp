#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Box.h"

using namespace glm;

// Apartado 30
Box::Box(GLdouble length, Texture* texture, Texture* inwardsTexture, GLboolean modulate)
: BoxOutline(length, texture, inwardsTexture, modulate),
_length(length)
{
    // Solo una mesh porque a nivel de estructura es lo mismo el top que el bottom
	mTopMesh = Mesh::generateRectangleTexCor(_length, _length);

    // Colocar y rotar tapa y fondo según la matriz base de referencia

	mTopModelMat = glm::translate(mBaseMat, glm::vec3(0.0, _length/2, 0.0));
	mTopModelMat = glm::rotate(mTopModelMat, glm::half_pi<GLfloat>(), glm::vec3(1.0, 0.0, 0.0));

	mBottomModelMat = glm::translate(mBaseMat, glm::vec3(0.0, -_length/2, 0.0));
	mBottomModelMat = glm::rotate(mBottomModelMat, glm::half_pi<GLfloat>(), glm::vec3(-1.0, 0.0, 0.0));
}


Box::~Box()
{
	delete mTopMesh;
	mTopMesh = nullptr;
}

void 
Box::render (const glm::mat4& modelViewMat) const
{
    // Renderiza el outline de la caja
	BoxOutline::render(modelViewMat);

    // Renderiza la tapa el fondo de la caja con las dos texturas (la secundaria reside en BoxOutline)

	if (mTopMesh != nullptr) {
		
		mat4 aMat = modelViewMat * mBottomModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", static_cast<bool>(mModulate));
		upload(aMat);

		glEnable(GL_CULL_FACE);

			glCullFace(GL_FRONT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mTexture != nullptr) mTexture->bind();
			mTopMesh->render();
			if (mTexture != nullptr) mTexture->unbind();

			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mInwardsTexture != nullptr) mInwardsTexture->bind();
			mTopMesh->render();
			if (mInwardsTexture != nullptr) mInwardsTexture->unbind();
		
		glDisable(GL_CULL_FACE);


		aMat = modelViewMat * mTopModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", static_cast<bool>(mModulate));
		upload(aMat);

		glEnable(GL_CULL_FACE);

			glCullFace(GL_FRONT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mTexture != nullptr) mTexture->bind();
			mTopMesh->render();
			if (mTexture != nullptr) mTexture->unbind();

			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mInwardsTexture != nullptr) mInwardsTexture->bind();
			mTopMesh->render();
			if (mInwardsTexture != nullptr) mInwardsTexture->unbind();
		
		glDisable(GL_CULL_FACE);
	}
}

// Apartado 31
//COMENTAR
void 
Box::update()
{
    // Coloca la matriz de la caja en la cara superior
	mTopModelMat = glm::translate(mBaseMat, glm::vec3(0.0f, _length/2, -_length/2));

    // Ajusta la direccion de apertura según si ha llegado a pi/2 o a 0, es decir, que se ha girado 90 grados
	if (_openAngle >= glm::half_pi<GLfloat>() || _openAngle <= 0.0)
		_dir = -_dir;

    // Avanza (sumando o restando) el angulo segun OPEN_ANGLE_SPEED. Denotar que dir siempre es +-1
	_openAngle = clamp<GLfloat>(_openAngle + (_dir * OPEN_ANGLE_SPEED), 0.0, glm::half_pi<GLfloat>());

    // Rota la cara restando el angulo a pi/2 porque por defecto la tapa está girada 90 grados
	mTopModelMat = glm::rotate(mTopModelMat, glm::half_pi<GLfloat>() - _openAngle, glm::vec3(1.0, 0.0, 0.0));
	// Avanza _length/2 en las coordenadas locales haciendo que esté pegada a un borde de la caja
    mTopModelMat = glm::translate(mTopModelMat, glm::vec3(0.0f, _length/2, 0.0f));
}

void Box::load()
{
	Abs_Entity::load();

	// solo 1 porque top y bottom son la misma mesh
	mTopMesh->load();
}
void Box::unload()
{
	Abs_Entity::unload();
	// solo 1 porque top y bottom son la misma mesh
	mTopMesh->unload();
}

void Box::setBaseMat(glm::mat4& baseMat)
{
	Abs_Entity::setBaseMat(baseMat);

	mTopModelMat = glm::translate(mBaseMat, glm::vec3(0.0, _length/2, 0.0));
	mTopModelMat = glm::rotate(mTopModelMat, glm::half_pi<GLfloat>(), glm::vec3(1.0, 0.0, 0.0));

	mBottomModelMat = glm::translate(mBaseMat, glm::vec3(0.0, -_length/2, 0.0));
	mBottomModelMat = glm::rotate(mBottomModelMat, glm::half_pi<GLfloat>(), glm::vec3(-1.0, 0.0, 0.0));
}