#include "Mesh.h"

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
 : mVAO(NONE)
 , mVBO(NONE)
 , mCBO(NONE)
 , mTCO(NONE)
{
}

Mesh::~Mesh()
{
	unload();
}

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::load()
{
	assert(mVBO == NONE); // not already loaded

	if (vVertices.size() > 0) { // transfer data
		glGenBuffers(1, &mVBO);
		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(vec3), vVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
		glEnableVertexAttribArray(0);

		if (vColors.size() > 0) {             // upload colors
			glGenBuffers(1, &mCBO);

			glBindBuffer(GL_ARRAY_BUFFER, mCBO);
			glBufferData(GL_ARRAY_BUFFER, vColors.size() * sizeof(vec4), vColors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
			glEnableVertexAttribArray(1);
		}

		if (vTexCoords.size() > 0)
		{
			glGenBuffers(1, &mTCO);
			glBindBuffer(GL_ARRAY_BUFFER, mTCO);
			glBufferData(GL_ARRAY_BUFFER,
			vTexCoords.size() * sizeof(vec2),
			vTexCoords.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			sizeof(vec2), nullptr);
			glEnableVertexAttribArray(2);
		}
	}
}

void
Mesh::unload()
{
	if (mVAO != NONE) {
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		mVAO = NONE;
		mVBO = NONE;

		if (mCBO != NONE) {
			glDeleteBuffers(1, &mCBO);
			mCBO = NONE;
		}

		if (mTCO != NONE) glDeleteBuffers(1, &mTCO);
	}
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();

	// Restablecer a LINE para setear un tipo de renderizado de poligonos por defecto
	// si quieres un renderizado especifico, lo implementas en tu entidad
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

// Apartado 2
Mesh*
Mesh::generateRegularPolygon(GLuint num, GLdouble r)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);
	
	GLdouble angleStep = radians(360.0) / num;

	GLdouble angle = radians(90.0);

	for (GLulong i = 0; i < num; ++i)
	{
		mesh->vVertices.emplace_back(r * cos(angle), r * sin(angle), 0.0);
		angle += angleStep;
	}

	return mesh;
}

// Apartado 6
Mesh*
Mesh::generateRGBTriangle(GLdouble r)
{
	Mesh* mesh = generateRegularPolygon(3, r);

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->vColors.reserve(mesh->mNumVertices);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

// Apartado 8
Mesh* 
Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	GLdouble halfW = w/2;
	GLdouble halfH = h/2;

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(halfW, halfH, 0);
	mesh->vVertices.emplace_back(-halfW, halfH, 0);
	mesh->vVertices.emplace_back(halfW, -halfH, 0);
	mesh->vVertices.emplace_back(-halfW, -halfH, 0);

	return mesh;
}

Mesh* 
Mesh::generateRGBRectangle(GLdouble w, GLdouble h)
{
	Mesh* mesh = generateRectangle(w, h);

	mesh->vColors.reserve(mesh->mNumVertices);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

//Apartado 15
Mesh* 
Mesh::generateCube(GLdouble length)
{
	Mesh* mesh = new Mesh();

	// Se que se puede hacer con triangles y es mas practico para desarrollar
	// lo he hecho con triangle strip simplemente como reto personal

	// En caso de querer hacer triangles simplemente habria que ir haciendo cada cara
	// dando una cantidad total de 36 vertices 
	mesh->mPrimitive = GL_TRIANGLES;

	GLdouble halfLength = length/2.;

	vec3 oneDown = {halfLength, -halfLength, halfLength};
	vec3 twoDown = {-halfLength, -halfLength, halfLength};;
	vec3 threeDown = {-halfLength, -halfLength, -halfLength};;
	vec3 fourDown = {halfLength, -halfLength, -halfLength};;

	vec3 oneUp = {halfLength, halfLength, halfLength};
	vec3 twoUp = {-halfLength, halfLength, halfLength};;
	vec3 threeUp = {-halfLength, halfLength, -halfLength};;
	vec3 fourUp = {halfLength, halfLength, -halfLength};;

	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// Cara inferior
	mesh->vVertices.emplace_back(oneDown);
	mesh->vVertices.emplace_back(twoDown);
	mesh->vVertices.emplace_back(threeDown);

	mesh->vVertices.emplace_back(oneDown);
	mesh->vVertices.emplace_back(threeDown);
	mesh->vVertices.emplace_back(fourDown);

	// Cara superior

	mesh->vVertices.emplace_back(oneUp);
	mesh->vVertices.emplace_back(fourUp);
	mesh->vVertices.emplace_back(twoUp);

	mesh->vVertices.emplace_back(threeUp);
	mesh->vVertices.emplace_back(twoUp);
	mesh->vVertices.emplace_back(fourUp);
	
	// Cara frontal
	mesh->vVertices.emplace_back(oneDown);
	mesh->vVertices.emplace_back(oneUp);
	mesh->vVertices.emplace_back(twoUp);

	mesh->vVertices.emplace_back(oneDown);
	mesh->vVertices.emplace_back(twoUp);
	mesh->vVertices.emplace_back(twoDown);

	// Cara trasera

	mesh->vVertices.emplace_back(threeDown);
	mesh->vVertices.emplace_back(threeUp);
	mesh->vVertices.emplace_back(fourUp);

	mesh->vVertices.emplace_back(threeDown);
	mesh->vVertices.emplace_back(fourUp);
	mesh->vVertices.emplace_back(fourDown);

	// Cara derecha

	mesh->vVertices.emplace_back(oneDown);
	mesh->vVertices.emplace_back(fourUp);
	mesh->vVertices.emplace_back(oneUp);

	mesh->vVertices.emplace_back(oneDown);
	mesh->vVertices.emplace_back(fourDown);
	mesh->vVertices.emplace_back(fourUp);

	// Cara izquierda

	mesh->vVertices.emplace_back(threeDown);
	mesh->vVertices.emplace_back(twoUp);
	mesh->vVertices.emplace_back(threeUp);

	mesh->vVertices.emplace_back(threeDown);
	mesh->vVertices.emplace_back(twoDown);
	mesh->vVertices.emplace_back(twoUp);

	return mesh;
}

void setFacesColor(vector<glm::vec4>& vColors, const vec4& color)
{
	for (int i = 0; i < 12; i++)
		vColors.emplace_back(color);
}

//Apartado 16
Mesh* 
Mesh::generateRGBCube(GLdouble length)
{
	Mesh* mesh = generateCube(length);

	mesh->vColors.reserve(mesh->mNumVertices);

	setFacesColor(mesh->vColors, {0.0, 0.0, 1.0, 1.0});
	setFacesColor(mesh->vColors, {1.0, 0.0, 0.0, 1.0});
	setFacesColor(mesh->vColors, {0.0, 1.0, 0.0, 1.0});

	return mesh;
}

// Apartado 20 y 21
Mesh*
Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* mesh = generateRectangle(w, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	// Multiplicar las coordenadas respectivas para que se haga tiling según rw y rh
	// El tiling ya está activado
	mesh->vTexCoords.emplace_back(1. * rw, 1.* rh);
	mesh->vTexCoords.emplace_back(0., 1.* rh);
	mesh->vTexCoords.emplace_back(1. * rw, 0.);
	mesh->vTexCoords.emplace_back(0., 0.);

	return mesh;
}

// Apartado 22
Mesh* 
Mesh::generateBoxOutline(GLdouble length)
{
	GLdouble halfL = length/2;

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// Se añaden los vertices de tal forma que las caras se generan en una "línea"
	// como cerrando un loop
	mesh->vVertices.emplace_back(-halfL, -halfL, halfL);
	mesh->vVertices.emplace_back(-halfL, halfL, halfL);
	mesh->vVertices.emplace_back(halfL, -halfL, halfL);
	mesh->vVertices.emplace_back(halfL, halfL, halfL);
	mesh->vVertices.emplace_back(halfL, -halfL, -halfL);
	mesh->vVertices.emplace_back(halfL, halfL, -halfL);
	mesh->vVertices.emplace_back(-halfL, -halfL, -halfL);
	mesh->vVertices.emplace_back(-halfL, halfL, -halfL);
	mesh->vVertices.emplace_back(-halfL, -halfL, halfL);
	mesh->vVertices.emplace_back(-halfL, halfL, halfL);

	return mesh;
}

// Apartado 24
// COMENTAR
Mesh*
Mesh::generateBoxOutlineTextCor(GLdouble length)
{
	Mesh* mesh = generateBoxOutline(length);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	// 5 veces por cada cara, todas las caras tienen la textura de la misma forma, son una serie
	// Si desdoblamos la malla es secuencial
	for (GLint i = 0; i < 5; ++i)
	{
		mesh->vTexCoords.emplace_back(0.+i, 0.);
		mesh->vTexCoords.emplace_back(0.+i, 1.);
	}

	return mesh;
}

// Apartado 26
Mesh* 
Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	// 2 extras, 1 para el inicial y otro para el final que es el único redundante
	mesh->mNumVertices = (np*2) +2;
	mesh->vVertices.reserve(mesh->mNumVertices);
	
	// Radio de punta interna
	GLdouble ri = re/2;

	// Calcula segun las puntas cuanto avanzar, teniendo en cuenta que por punta hay 2 vertices (grande y pequeño)
	GLdouble angleStep = radians(360.0) / (np*2);

	// Angulo donde se va a colocar el punto, empieza arriba
	GLdouble angle = radians(90.0);

	// Añade vértice ancla de triangle fan en 0,0,0
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);

	// Cada paso pinta la punta externa y la interna
	for (GLulong i = 0; i < np; ++i)
	{
		mesh->vVertices.emplace_back(re * cos(angle), re * sin(angle), h);
		angle += angleStep;
		mesh->vVertices.emplace_back(ri * cos(angle), ri * sin(angle), h);
		angle += angleStep;
	}

	// Cerrar la estrella
	mesh->vVertices.emplace_back(re * cos(angle), re * sin(angle), h);

	return mesh;
}

/// @brief Devuelve el punto siguiente de un cuadrado según en que punto del perimetro en el que se está
/// 	   y lo que se debe avanzar si pensamos en el perimetro como en un numero que va del 0 al 4,
///		   empieza en 0,0 y avanza en el perimetro yendo hacia arriba primero hasta volver a 0,0. \n
///		
///		   Se asume que el punto introducido está en el perimetro de un cuadrado de lado 1. Si se mete cualquier
///		   otro punto el resultado es desconocido
/// @param progress la cantidad de perimetro a avanzar, está entre 0 y 4
/// @param currentTexPoint el punto del perimetro en el que se está
void getPointInSquarePerimeter(GLdouble progress, glm::vec2& currentTexPoint)
{
	GLdouble currentProgress = progress;

	while (currentProgress != 0.0f)
	{
		if (currentTexPoint.x == 0.0f && currentTexPoint.y >= 0.0f && currentTexPoint.y < 1.0f)
		{
			currentTexPoint.y += progress;

			if (currentTexPoint.y <= 1.0f)
				currentProgress = 0.0f;
			else
			{
				currentProgress = currentProgress - (currentTexPoint.y - 1.0f);
				currentTexPoint.y = 1.0f;
			}
		}
		else if (currentTexPoint.x >= 0.0f && currentTexPoint.x < 1.0f && currentTexPoint.y == 1.0f)
		{
			currentTexPoint.x += progress;
			if (currentTexPoint.x <= 1.0f)
				currentProgress = 0.0f;
			else
			{
				currentProgress = currentProgress - (currentTexPoint.x - 1.0f);
				currentTexPoint.x = 1.0f;
			}
		}
		else if (currentTexPoint.x == 1.0f && currentTexPoint.y <= 1.0f && currentTexPoint.y > 0.0f)
		{
			currentTexPoint.y -= progress;
			if (currentTexPoint.y >= 0.0f)
				currentProgress = 0.0f;
			else
			{
				currentProgress =  -(currentTexPoint.y + 1.0f);
				currentTexPoint.y = 0.0f;
			}
		}
		else if (currentTexPoint.x > 0.0f && currentTexPoint.y == 0.0f)
		{
			currentTexPoint.x -= progress;
			if (currentTexPoint.x >= 0.0f)
				currentProgress = 0.0f;
			else
			{
				currentProgress = -(currentTexPoint.x + 1.0f);
				currentTexPoint.x = 0.0f;
			}
		}
	}
}

// Apartado 29
/// genera las coordenadas de textura de la estrella, seccionando la textura en "triangulos",
/// como si se cortara una tarta/pizza
Mesh* 
Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = generateStar3D(re, np, h);

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	// Vertice inicial en el centro para que se desdoble como un "cono"
	mesh->vTexCoords.emplace_back(0.5, 0.5);

	// Si el perimetro mide 4, segun las puntas que tengamos se obtiene la cantidad de perimetro que cubre de un vertice
	// a otro de la estrella
	GLdouble progress = 4.0 / (np*2);

	glm::vec2 currentTexPoint = {0.5, 1.0};

	// Avanza uno extra para cerrar
	for (GLint i = 0; i <= np*2; ++i)
	{
		mesh->vTexCoords.emplace_back(currentTexPoint);
		getPointInSquarePerimeter(progress, currentTexPoint);
	}

	return mesh;
}