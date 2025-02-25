#include "Scene3.h"

/// @brief 
/// Escena de la practica 2 de IG
void
Scene3::init()
{
	setGL(); // OpenGL settings

	Texture* texturaBaldosa = new Texture();
	texturaBaldosa->load("baldosaC.png");

	gTextures.push_back(texturaBaldosa);

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
    gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new Ground(600.0, 600.0, texturaBaldosa, false));


}