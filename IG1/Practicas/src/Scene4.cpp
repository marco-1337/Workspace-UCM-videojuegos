#include "Scene4.h"

#include "Torus.h"

void
Scene4::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new Torus({0., 1., 0., 1.}, 400., 150., 12));
}