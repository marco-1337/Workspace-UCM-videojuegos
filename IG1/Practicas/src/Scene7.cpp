#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene7.h"

#include "AdvancedTIE.h"
#include "CompoundEntity.h"
#include "Sphere.h"
#include "Texture.h"

#include "IG1App.h"

#include "Camera.h"

using namespace glm;

void
Scene7::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights

	// Textures
	Texture* wingTex = new Texture();
	wingTex->load("noche.jpg", 200);
	gTextures.push_back(wingTex);

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

    Sphere* tatooine = new Sphere(500., 40, 40);
    tatooine->setColor({255./255., 233./255., 0., 1.});
    gObjects.push_back(tatooine);

    inventedNode = new CompoundEntity();
    AdvancedTIE* tie = new AdvancedTIE(0.1, wingTex);
    inventedNode->addEntity(tie);
    tie->setModelMat(translate(mat4(1.0), vec3(0. , 550., 0.)));

	gObjects.push_back(inventedNode);
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
    inventedNode->setModelMat
    (
        glm::rotate
        (
            inventedNode->modelMat(),
            radians<GLfloat>(3.0), 
            vec3(1., 0., 0.)
        )
    );
}

void
Scene7::rotate()
{
    inventedNode->setModelMat
    (
        glm::rotate
        (
            inventedNode->modelMat(),
            radians<GLfloat>(6.0), 
            vec3(0., 1., 0.)
        )
    );
}