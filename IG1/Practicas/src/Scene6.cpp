#include "Scene6.h"

#include "AdvancedTIE.h"
#include "Texture.h"

void
Scene6::init()
{
	setGL(); // OpenGL settings

    Scene::init();

	// allocate memory and load resources
	// Lights

	// Textures
	Texture* wingTex = new Texture();
	wingTex->load("noche.jpg", 200);
	gTextures.push_back(wingTex);

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new AdvancedTIE(0.5, wingTex));
}

void
Scene6::load()
{
	glClearColor(0., 0., 0., 1.0);
    Scene::load();
}

void
Scene6::unload()
{
    glClearColor(0.6, 0.7, 0.8, 1.0);
    Scene::unload();
}