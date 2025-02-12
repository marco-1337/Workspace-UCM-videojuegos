#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

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
}

void
Scene::setGL()
{
	// OpenGL basic setting
	//glClearColor(1.0, 1.0, 1.0, 1.0); // background color (alpha=1 -> opaque)

	// Apartado 1
	glClearColor(0.6, 0.7, 0.8, 1.0);
	
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());
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