#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Abs_Entity::upload(const mat4& modelViewMat) const
{
	mShader->setUniform("modelView", modelViewMat);
}

Abs_Entity::~Abs_Entity()
{
	delete mMesh;
	mMesh = nullptr;
}

void
Abs_Entity::load()
{
	mMesh->load();
}

void
Abs_Entity::unload()
{
	mMesh->unload();
}

EntityWithColors::EntityWithColors()
{
	mShader = Shader::get("vcolors");
}

void
EntityWithColors::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mMesh->render();
	}
}

RGBAxes::RGBAxes(GLdouble l)
{
	mShader = Shader::get("vcolors");
	mMesh = Mesh::createRGBAxes(l);
}

// Apartado 3
SingleColorEntity::SingleColorEntity(glm::dvec4 color): mColor(color)
{
	mShader = Shader::get("simple");
}

glm::dvec4 
SingleColorEntity::color() const { return mColor; }

void
SingleColorEntity::setColor(glm::dvec4 color) 
{
	mColor = color; 
}

void
SingleColorEntity::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("color", static_cast<glm::vec4>(mColor));
		upload(aMat);
		mMesh->render();
	}
}
// !Apartado 3

// Apartado 4
RegularPolygon::RegularPolygon(GLuint num, GLdouble r, glm::dvec4 color): SingleColorEntity(color)
{
	mMesh = Mesh::generateRegularPolygon(num, r);
}

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

	mModelMat = glm::translate(mat4(1), posNueva);
	mModelMat = glm::rotate(mModelMat, _anguloRotacion, glm::vec3(0, 0, -1));
}

// Apartado 8
RGBRectangle::RGBRectangle(GLdouble w, GLdouble h): EntityWithColors()
{
	mMesh = Mesh::generateRGBRectangle(w, h);
}

// Apartado 8
void
RGBRectangle::render(const glm::mat4& modelViewMat) const
{
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
	if (_rotaciones.x < glm::pi<GLfloat>())
	{
		_rotaciones.x = clamp<GLfloat>(_rotaciones.x + 0.04, 0.0, glm::pi<GLfloat>());
		mModelMat = glm::rotate(mat4(1), _rotaciones.x, glm::vec3(1, 0, 0));
		mModelMat = glm::translate(mModelMat, {_length/2, _length/2, -_length/2});
	}
	else if (_rotaciones.z < glm::pi<GLfloat>())
	{
		mModelMat = glm::rotate(mat4(1), glm::pi<GLfloat>(), glm::vec3(1, 0, 0));

		_rotaciones.z = clamp<GLfloat>(_rotaciones.z + 0.04, 0.0, glm::pi<GLfloat>());
		mModelMat = glm::rotate(mModelMat, _rotaciones.z, glm::vec3(0, 0, -1));
		mModelMat = glm::translate(mModelMat, {_length/2, _length/2, -_length/2});
	}
	else if (_rotaciones.y < glm::pi<GLfloat>())
	{
		mModelMat = glm::rotate(mat4(1), glm::pi<GLfloat>(), glm::vec3(1, 0, 0));
		mModelMat = glm::rotate(mModelMat, glm::pi<GLfloat>(), glm::vec3(0, 0, -1));

		_rotaciones.y = clamp<GLfloat>(_rotaciones.y + 0.04, 0.0, glm::pi<GLfloat>());
		mModelMat = glm::rotate(mModelMat, _rotaciones.y, glm::vec3(0, 1, 0));
		mModelMat = glm::translate(mModelMat, {_length/2, _length/2, -_length/2});
	}
	else 
		_rotaciones = {0., 0., 0.};
}

// Apartado 18
// COMENTAR
Ground::Ground(GLdouble w, GLdouble h, Texture* texture, GLboolean modulate, GLint rw, GLint rh)
: EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateRectangleTexCor(w, h, rw, rh);
	mModelMat = glm::rotate(mModelMat, glm::half_pi<GLfloat>(), glm::vec3(-1, 0, 0));
}

// Apartado 19
EntityWithTexture::EntityWithTexture(Texture* texture, GLboolean modulate)
{
	mTexture = texture;
	mModulate = modulate;
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

		glEnable(GL_CULL_FACE);

			glCullFace(GL_FRONT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mTexture != nullptr) mTexture->bind();
			mMesh->render();
			if (mTexture != nullptr) mTexture->unbind();

			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mInwardsTexture != nullptr) mInwardsTexture->bind();
			mMesh->render();
			if (mInwardsTexture != nullptr) mInwardsTexture->unbind();
		
		glDisable(GL_CULL_FACE);
	}
}

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
	mModelMat = glm::rotate(glm::mat4(1), _yRotation += ROTATION_SPEED, glm::vec3(0, 1, 0));
	mModelMat = glm::rotate(mModelMat, _zRotation += ROTATION_SPEED, glm::vec3(0, 0, 1));
}

// Apartado 30
// COMENTAR
Box::Box(GLdouble length, Texture* texture, Texture* inwardsTexture, GLboolean modulate)
: BoxOutline(length, texture, inwardsTexture, modulate),
_length(length)
{
	mTopMesh = Mesh::generateRectangleTexCor(length, length);
	mTopModelMat = glm::translate(glm::mat4(1), glm::vec3(0.0, _length/2, 0.0));
	mTopModelMat = glm::rotate(mTopModelMat, glm::half_pi<GLfloat>(), glm::vec3(1.0, 0.0, 0.0));

	mBottomMesh = mTopMesh;
	mBottomModelMat = glm::translate(glm::mat4(1), glm::vec3(0.0, -_length/2, 0.0));
	mBottomModelMat = glm::rotate(mBottomModelMat, glm::half_pi<GLfloat>(), glm::vec3(-1.0, 0.0, 0.0));
}

Box::~Box()
{
	delete mTopMesh;

	mTopMesh = nullptr;
	mBottomMesh = nullptr;
}

void 
Box::render (const glm::mat4& modelViewMat) const
{
	BoxOutline::render(modelViewMat);

	if (mBottomMesh != nullptr) {
		
		mat4 aMat = modelViewMat * mBottomModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", static_cast<bool>(mModulate));
		upload(aMat);

		glEnable(GL_CULL_FACE);

			glCullFace(GL_FRONT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mTexture != nullptr) mTexture->bind();
			mBottomMesh->render();
			if (mTexture != nullptr) mTexture->unbind();

			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (mInwardsTexture != nullptr) mInwardsTexture->bind();
			mBottomMesh->render();
			if (mInwardsTexture != nullptr) mInwardsTexture->unbind();
		
		glDisable(GL_CULL_FACE);
	}

	if (mTopMesh != nullptr) {
		mat4 aMat = modelViewMat * mTopModelMat; // glm matrix multiplication
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
// COMENTAR
void 
Box::update()
{
	mTopModelMat = glm::translate(glm::mat4(1), glm::vec3(0.0f, _length/2, -_length/2));

	if (_openAngle >= glm::half_pi<GLfloat>() || _openAngle <= 0.0)
		_dir = -_dir;

	_openAngle = clamp<GLfloat>(_openAngle + (_dir * OPEN_ANGLE_SPEED), 0.0, glm::half_pi<GLfloat>());

	mTopModelMat = glm::rotate(mTopModelMat, glm::half_pi<GLfloat>() - _openAngle, glm::vec3(1.0, 0.0, 0.0));
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