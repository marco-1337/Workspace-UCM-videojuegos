#include "Scene1.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Apartado 9
void
Scene1::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	// Apartado 8
	gObjects.push_back(new RGBRectangle(700., 350.));

	// Apartado 10
	GLdouble radius = 350.;
	RGBTriangle* triangle = new RGBTriangle(50.);

	//Apartado 11
	triangle->setModelMat(glm::translate(triangle->modelMat(), {radius, 0., 0.}));

	// Apartado 10
	gObjects.push_back(triangle);
	gObjects.push_back(new RegularPolygon(50, radius, {1.0, 1.0, 1.0, 1.0}));
}