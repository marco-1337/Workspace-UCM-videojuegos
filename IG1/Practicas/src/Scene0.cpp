#include "Scene0.h"

// Apartado 9
void
Scene0::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	// Apartado 5
	gObjects.push_back(new RegularPolygon(3, 300.0, {1.0, 0.0, 1.0, 1.0}));
	gObjects.push_back(new RegularPolygon(50, 300.0, {0.0, 1.0, 1.0, 1.0}));
}