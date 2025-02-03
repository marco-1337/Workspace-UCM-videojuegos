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
		mShader->setUniform("color", static_cast<glm::vec4>(mColor));
		mShader->use();
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