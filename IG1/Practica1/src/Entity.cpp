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
	load();
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
	load();
}

// Apartado 6
RGBTriangle::RGBTriangle(GLdouble r): EntityWithColors()
{
	mMesh = Mesh::generateRGBTriangle(r);
	load();
}

// Apartado 7
void
RGBTriangle::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modelView", aMat);

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

// Apartado 8
RGBRectangle::RGBRectangle(GLdouble w, GLdouble h): EntityWithColors()
{
	mMesh = Mesh::generateRGBRectangle(w, h);
	load();
}

// Apartado 8
void
RGBRectangle::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modelView", aMat);

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