#include "Scene2.h"

#include "Cube.h"
#include "RGBCube.h"

void
Scene2::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new Cube(350.));
	gObjects.push_back(new RGBCube(350.));
}