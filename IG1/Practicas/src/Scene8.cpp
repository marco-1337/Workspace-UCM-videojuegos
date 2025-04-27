#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene8.h"

#include "Sphere.h"

#include "IG1App.h"

#include "Camera.h"

using namespace glm;

void
Scene8::init()
{
	setGL(); // OpenGL settings

    Scene::init();

	// allocate memory and load resources
	// Lights
	// Textures

    Material goldenMaterial = Material();

    goldenMaterial.setAmb({0.24725, 0.1995, 0.0745});
    goldenMaterial.setDiff({0.75164, 0.60648, 0.22648});
    goldenMaterial.setSpec({0.628281, 0.555902, 0.366065});
    goldenMaterial.setExp(51.2);

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

    Sphere* tatooineYellow = new Sphere({255./255., 233./255., 0., 1.}, 100., 40, 40);
    tatooineYellow->setModelMat(translate(mat4(1.0), vec3(200. , 0., 0.)));

    Sphere* tatooineGolden = new Sphere({255./255., 233./255., 0., 1.}, 100., 40, 40);
    tatooineGolden->setMaterial(goldenMaterial);
    tatooineGolden->setModelMat(translate(mat4(1.0), vec3(0. , 0., 200.)));

    gObjects.push_back(tatooineYellow);
    gObjects.push_back(tatooineGolden);
}