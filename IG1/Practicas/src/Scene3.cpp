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

	Texture* texturaMadera = new Texture();
	texturaMadera->load("container.jpg");
	gTextures.push_back(texturaMadera);

	Texture* texturaMaderaInterna = new Texture();
	texturaMaderaInterna->load("papelE.png");
	gTextures.push_back(texturaMaderaInterna);

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
    gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new Ground(600.0, 600.0, texturaBaldosa, false, 4, 4));
	gObjects.push_back(new BoxOutline(100., texturaMadera, texturaMaderaInterna));

}