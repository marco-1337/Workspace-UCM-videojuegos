#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene::init()
{
	dirLight = new DirLight(0);

	dirLight->setAmb({.25, .25, .25});
	dirLight->setDiff({.6, .6, .6});
	dirLight->setSpec({.0, .2, .0});
	dirLight->setEnabled(true);
	gLights.push_back(dirLight);
}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects)
		delete el;

	gObjects.clear();

	for (Texture* tx : gTextures)
		delete tx;

	gTextures.clear();

	for (Light* lg : gLights)
		delete lg;
	
	gLights.clear();
}

void
Scene::load()
{
	for (Abs_Entity* obj : gObjects)
		obj->load();
}

void
Scene::unload()
{
	for (Abs_Entity* obj : gObjects)
		obj->unload();

	Shader& lightShader = *(Shader::get("light"));

	lightShader.use();

	for (Light* lg : gLights)
		lg->unload(lightShader);
}

void
Scene::setGL()
{
	// OpenGL basic setting
	//glClearColor(1.0, 1.0, 1.0, 1.0); // background color (alpha=1 -> opaque)

	// Apartado 1
	glClearColor(0.6, 0.7, 0.8, 1.0);
	
	glEnable(GL_DEPTH_TEST);          // enable Depth test
	//glEnable(GL_TEXTURE_2D); // Activar las texturas en la escena
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	//glDisable(GL_TEXTURE_2D); // Desactivar las texturas en la escena
}

void
Scene::uploadLights(Camera const& cam) const
{
	Shader& lightShader = *(Shader::get("light"));

	lightShader.use();

	for (Light* lg : gLights) lg->upload(lightShader, cam.viewMat());

	for (Abs_Entity* el : gObjects) el->uploadLights(lightShader, cam.viewMat());
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	// Cargar luces antes de renderizar
	uploadLights(cam);

	for (Abs_Entity* el : gObjects) el->render(cam.viewMat());
}

// Apartado 12
void
Scene::update()
{
	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}
}

// Apartado 74
void 
Scene::switchDirLight()
{
	if (dirLight != nullptr)
	{
		dirLight->setEnabled(!dirLight->enabled());
	}
}