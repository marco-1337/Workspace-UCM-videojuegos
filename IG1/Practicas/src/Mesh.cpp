#include "Mesh.h"

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
 : mVAO(NONE)
 , mVBO(NONE)
 , mCBO(NONE)
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
	}
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();
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