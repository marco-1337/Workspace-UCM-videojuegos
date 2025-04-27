#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "Light.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init();

	virtual void render(Camera const& cam) const;
	void update();

	// load or unload scene data into the GPU
	virtual void load();
	virtual void unload();

	// Apartado 74
	void switchDirLight();

	virtual GLboolean sceneKeyPress(GLchar) { return false; }

protected:
	void destroy();
	void setGL();
	void resetGL();

	// Apartado 73
	void uploadLights(Camera const& cam) const;

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;
	std::vector<Light*> gLights;

	DirLight* dirLight = nullptr;
};
#endif //_H_Scene_H_