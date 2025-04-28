#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene7.h"

#include "AdvancedTIE.h"
#include "CompoundEntity.h"
#include "Sphere.h"
#include "Texture.h"
#include "Light.h"

#include "IG1App.h"

#include "Camera.h"

using namespace glm;

void
Scene7::init()
{
	setGL(); // OpenGL settings

    Scene::init();

    Material goldenMaterial = Material();

    goldenMaterial.setAmb({0.24725, 0.1995, 0.0745});
    goldenMaterial.setDiff({0.75164, 0.60648, 0.22648});
    goldenMaterial.setSpec({0.628281, 0.555902, 0.366065});
    goldenMaterial.setExp(51.2);

	// allocate memory and load resources

// Lights

    // Luz posicional en el plano XZ
    posLight = new PosLight(0);
    posLight->setPosition(vec3(1000., 1000., .0));
    posLight->setAttenuation(1.5, 0., 0.);
	posLight->setAmb({.25, .25, .25});
	posLight->setDiff({1., 1., .0});
	posLight->setSpec({.0, .2, .0});
	posLight->setEnabled(true);
	gLights.push_back(posLight);

    // Foco en el plano YZ (en el eje Z)
    spotLight = new SpotLight(vec3(.0, .0, 550.), 0);
    spotLight->setCutoff(40., 45.);
    spotLight->setDirection(vec3(0., 0., -1));
    spotLight->setAttenuation(1, 0., 0.);
	spotLight->setAmb({.25, .25, .25});
	spotLight->setDiff({.6, .6, .6});
	spotLight->setSpec({.0, .2, .0});
	spotLight->setEnabled(true);
	gLights.push_back(spotLight);

    // Inizializar la luz de exploracion del tie mirando hacia abajo
    tieLight = new SpotLight(vec3(.0, 21., 0.), 1);
    tieLight->setCutoff(30., 50.);
    tieLight->setDirection(vec3(0., -1., 0.));
    tieLight->setAttenuation(1, 0., 0.);
	tieLight->setAmb({.25, .25, .25});
	tieLight->setDiff({.6, .6, .6});
	tieLight->setSpec({.0, .2, .0});
	tieLight->setEnabled(true);
	gLights.push_back(tieLight);

// Textures

	Texture* wingTex = new Texture();
	wingTex->load("noche.jpg", 200);
	gTextures.push_back(wingTex);

// Graphics objects (entities) of the scene

    Sphere* tatooine = new Sphere({255./255., 233./255., 0., 1.}, 500., 40, 40);
    tatooine->setMaterial(goldenMaterial);

    // Tie despues de tatooine porque contiene las alas traslucidas
    tieInventedNode = new CompoundEntity();
    AdvancedTIE* tie = new AdvancedTIE(0.1, wingTex);
    // Añadir luz de exploracion
    tie->addLight(tieLight);
    tieInventedNode->addEntity(tie);
    // Colocar tie a la altura del planeta
    tie->setModelMat(translate(mat4(1.0), vec3(0. , 550., 0.)));
    // Rotacion del nodo para que el tie empiece con su forward (1, 0, 0)
    tieInventedNode->setModelMat
    (
        glm::rotate
        (
            tieInventedNode->modelMat(),
            radians<GLfloat>(90.0), 
            vec3(0., 1., 0.)
        )
    );

	gObjects.push_back(new RGBAxes(400.0));
    gObjects.push_back(tatooine);
	gObjects.push_back(tieInventedNode);
}

GLboolean
Scene7::sceneKeyPress(GLchar key) 
{
    GLboolean retVal = true;

    switch (key)
    {
        // Apartado 68
        case 'f':
            rotate();
            break;
        case 'g':
            orbit();
            break;
        case 't':
            if (posLight != nullptr) posLight->setEnabled(!posLight->enabled());
            break;
        case 'y':
            if (spotLight != nullptr) spotLight->setEnabled(!spotLight->enabled());
            break;
        case 'h':
            if (tieLight != nullptr) tieLight->setEnabled(!tieLight->enabled());
            break;
        default:
            retVal = false;
            break;
    }

    return retVal;
}

void
Scene7::load()
{
	glClearColor(0., 0., 0., 1.0);
    Scene::load();
}

void
Scene7::unload()
{
    glClearColor(0.6, 0.7, 0.8, 1.0);
    Scene::unload();
}

void
Scene7::orbit()
{
    tieInventedNode->setModelMat
    (
        glm::rotate
        (
            tieInventedNode->modelMat(),
            radians<GLfloat>(3.0), 
            vec3(1., 0., 0.)
        )
    );
}

void
Scene7::rotate()
{
    tieInventedNode->setModelMat
    (
        glm::rotate
        (
            tieInventedNode->modelMat(),
            radians<GLfloat>(6.0), 
            vec3(0., 1., 0.)
        )
    );
}