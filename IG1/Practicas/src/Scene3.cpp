#include "Scene3.h"
#include "IG1App.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Ground.h"
#include "Box.h"
#include "Photo.h"
#include "Star3D.h"
#include "Star3D.h"
#include "GlassParapet.h"

/// @brief 
/// Escena de la practica 2 de IG
void
Scene3::init()
{
	setGL(); // OpenGL settings

	// Inicializacion de las texturas

	Texture* texturaBaldosa = new Texture();
	texturaBaldosa->load("baldosaC.png");
	gTextures.push_back(texturaBaldosa);

	Texture* texturaMadera = new Texture();
	texturaMadera->load("container.jpg");
	gTextures.push_back(texturaMadera);

	Texture* texturaMaderaInterna = new Texture();
	texturaMaderaInterna->load("papelE.png");
	gTextures.push_back(texturaMaderaInterna);

	Texture* texturaEstrella = new Texture();
	texturaEstrella->load("baldosaP.png");
	gTextures.push_back(texturaEstrella);

	Texture* texturaVentana = new Texture();
	texturaVentana->load("windowV.jpg", 123);
	gTextures.push_back(texturaVentana);

	Texture* texturaFoto = new Texture();
	texturaFoto->loadColorBuffer(100, 100);
	gTextures.push_back(texturaFoto);

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	RGBAxes* rgbAxes = new RGBAxes(400.0);
    gObjects.push_back(rgbAxes);
	_opaqueEntities.push_back(rgbAxes);

	glm::mat4 baseMat;

	Ground* ground = new Ground(600.0, 600.0, texturaBaldosa, false, 4, 4);
	baseMat = glm::translate(glm::mat4(1), glm::vec3(0., -200., 0.));
	baseMat = glm::rotate(baseMat, glm::half_pi<GLfloat>(), glm::vec3(-1, 0, 0));
	ground->setBaseMat(baseMat);
	gObjects.push_back(ground);
	_opaqueEntities.push_back(ground);

	Box* box = new Box(100., texturaMadera, texturaMaderaInterna);
	baseMat = glm::translate(glm::mat4(1), glm::vec3(200., -100., 200.));
	box->setBaseMat(baseMat);
	gObjects.push_back(box);
	_opaqueEntities.push_back(box);

	Photo* photoFloor = new Photo(texturaFoto, 200.0, 150.0);
	baseMat = glm::translate(glm::mat4(1), glm::vec3(-200., 100., -200.));
	baseMat = glm::rotate(baseMat, glm::half_pi<GLfloat>(), glm::vec3(-1, 0, 0));
	photoFloor->setBaseMat(baseMat);
	_photoEntities.push_back(photoFloor);
	gObjects.push_back(photoFloor);
	_opaqueEntities.push_back(photoFloor);

	Star3D* star = new Star3D(50., 8, 70., texturaEstrella);
	baseMat = glm::translate(glm::mat4(1), glm::vec3(200., 100., 200.));
	star->setBaseMat(baseMat);
	gObjects.push_back(star);
	_opaqueEntities.push_back(star);

	GlassParapet* glassParapet = new GlassParapet(600., texturaVentana);
	gObjects.push_back(glassParapet);
	_translucentEntities.push_back(glassParapet);
}

void 
Scene3::load()
{
	Scene::load();

	for (Photo* p : _photoEntities)
		p->update();
}

void 
Scene3::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : _opaqueEntities)
		el->render(cam.viewMat());

	glDepthMask(GL_FALSE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (Abs_Entity* el : _translucentEntities)
			el->render(cam.viewMat());

		glDisable(GL_BLEND);

	glDepthMask(GL_TRUE);
}