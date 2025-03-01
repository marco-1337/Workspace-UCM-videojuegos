#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0)  // 4x4 identity matrix
	  , mShader(nullptr) {};
	virtual ~Abs_Entity();

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(const glm::mat4& modelViewMat) const = 0; // abstract method

	// Apartado 12
	virtual void update() {}

	// modeling matrix
	glm::mat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::mat4 const& aMat) { mModelMat = aMat; };

	// load or unload entity data into the GPU
	virtual void load();
	virtual void unload();

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::mat4 mModelMat;  // modeling matrix
	Shader* mShader; // shader

	// transfers modelViewMat to the GPU
	virtual void upload(const glm::mat4& mModelViewMat) const;
};

class EntityWithColors : public Abs_Entity
{
public:
	explicit EntityWithColors();
	void render(const glm::mat4& modelViewMat) const override;
};

class RGBAxes : public EntityWithColors
{
public:
	explicit RGBAxes(GLdouble l);
};

class SingleColorEntity : public Abs_Entity
{
public:
	explicit SingleColorEntity(glm::dvec4 color = glm::dvec4(0.0, 0.0, 0.0, 1.0));
	glm::dvec4 color() const;
	void setColor(glm::dvec4 color);

	void render(const glm::mat4& modelViewMat) const override;

protected:
	glm::dvec4 mColor;
};

// Apartado 4
class RegularPolygon : public SingleColorEntity 
{
public:
	explicit RegularPolygon(GLuint num, GLdouble r, glm::dvec4 color = glm::dvec4(0.0, 0.0, 0.0, 1.0));
};

class RGBTriangle : public EntityWithColors
{
public:
	explicit RGBTriangle(GLdouble r);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;
private:
	GLfloat _anguloRotacion = 0.;
};

class RGBRectangle : public EntityWithColors
{
public:
	explicit RGBRectangle(GLdouble w, GLdouble h);
	void render(const glm::mat4& modelViewMat) const override;
};

// Apartado 15
class Cube : public SingleColorEntity
{
public:
	explicit Cube(GLdouble length);
	void render(const glm::mat4& modelViewMat) const override;
};

// Apartado 16
class RGBCube : public EntityWithColors
{
public:
	explicit RGBCube(GLdouble length);
	void render(const glm::mat4& modelViewMat) const override;

	// Apartado 17
	void update() override;
private:
	GLdouble _length;
	glm::fvec3 _rotaciones = {0., 0., 0.};
};

// Apartado 19
class EntityWithTexture: public Abs_Entity
{
protected:
	Texture* mTexture;
	GLboolean mModulate; // indica si modulará la textura con el color de los vértices
public:
	explicit EntityWithTexture(Texture* texture, GLboolean modulate = false);
	void render (const glm::mat4& modelViewMat) const override;
};

// Apartado 18
class Ground: public EntityWithTexture
{
public:
	explicit Ground(GLdouble w, GLdouble h, Texture* texture, GLboolean modulate = false, GLint rw = 1, GLint rh = 1);
};

// Apartado 23
class BoxOutline: public EntityWithTexture
{
public:
	explicit BoxOutline(GLdouble length, Texture* texture, Texture* inwardsTexture, GLboolean modulate = false);
	void render (const glm::mat4& modelViewMat) const override;
protected:
	Texture* mInwardsTexture = nullptr; 
};

// Apartado 27
class Star3D: public EntityWithTexture
{
public:
	explicit Star3D(GLdouble re, GLuint np, GLdouble h, Texture* texture, GLboolean modulate = false);
	void render (const glm::mat4& modelViewMat) const override;
	// Apartado 28
	void update() override;
private:
	GLfloat _yRotation = 0.0;
	GLfloat _zRotation = 0.0;
	static constexpr GLfloat ROTATION_SPEED = 0.05;
};

// Apartado 30

class Box: public BoxOutline
{
public:
	explicit Box(GLdouble length, Texture* texture, Texture* inwardsTexture, GLboolean modulate = false);
	~Box();
	void render (const glm::mat4& modelViewMat) const override;
	void update() override;

	void load() override;
	void unload() override;
private:
	GLdouble _length;
	GLint _dir = -1;
	GLfloat _openAngle = 0.0;
	Mesh* mBottomMesh;
	glm::mat4 mBottomModelMat;
	Mesh* mTopMesh;
	glm::mat4 mTopModelMat;

	static constexpr GLfloat OPEN_ANGLE_SPEED = 0.05;
};
#endif //_H_Entities_H_