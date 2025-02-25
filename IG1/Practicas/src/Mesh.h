#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

class Mesh
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh

	// Apartado 2
	static Mesh* generateRegularPolygon(GLuint num, GLdouble r);
	// Apartado 6
	static Mesh* generateRGBTriangle(GLdouble r);
	// Apartado 8
	static Mesh* generateRectangle(GLdouble w, GLdouble h);
	static Mesh* generateRGBRectangle(GLdouble w, GLdouble h);
	// Apartado 15
	static Mesh* generateCube(GLdouble length);
	// Apartado 16
	static Mesh* generateRGBCube(GLdouble length);

	// Apartado 20
	static Mesh* generateRectangleTexCor(GLdouble w, GLdouble h);

	Mesh();
	virtual ~Mesh();

	Mesh(const Mesh& m) = delete;            // no copy constructor
	Mesh& operator=(const Mesh& m) = delete; // no copy assignment

	virtual void render() const;

	GLuint size() const { return mNumVertices; }; // number of elements
	std::vector<glm::vec3> const& vertices() const { return vVertices; };
	std::vector<glm::vec4> const& colors() const { return vColors; };
	std::vector<glm::dvec2> const& texCoords() const { return vTexCoords; }

	void load();
	void unload();

protected:
	GLuint mPrimitive =
	  GL_TRIANGLES;          // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0; // number of elements ( = vVertices.size())
	std::vector<glm::vec3> vVertices; // vertex array
	std::vector<glm::vec4> vColors;   // color array
	std::vector<glm::dvec2> vTexCoords; //texture array
	virtual void draw() const;

	GLuint mVAO;  // vertex array object

private:
	GLuint mVBO;  // vertex buffer object
	GLuint mCBO;  // color buffer object
	GLuint mTCO;
};

#endif //_H_Scene_H_
