#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class PosLight;

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0)  // 4x4 identity matrix
	  , mBaseMat(1.0)
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

	virtual void setBaseMat(glm::mat4& newMat) { mBaseMat = newMat; mModelMat = mBaseMat;}

	/// @brief Carga las luces posicionales del objeto relativas al objeto
	/// @param modelViewMat 
	virtual void uploadLights(Shader& shader, const glm::mat4& modelViewMat) const;

	void addLight(PosLight* light);

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::mat4 mModelMat;  // modeling matrix
	Shader* mShader; // shader

	glm::mat4 mBaseMat;

	// Apartado 77
    /// @brief Luces relativas al objeto
    std::vector<PosLight*> gPosLights;

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

#endif //_H_Entities_H_