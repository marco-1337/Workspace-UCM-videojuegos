#ifndef _H_IndexMesh_H_
#define _H_IndexMesh_H_

#include <numbers>

#include "Mesh.h"

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

// Apartado 54
class IndexMesh: public Mesh
{
public:
    std::vector<GLuint> vIndexes;
    GLuint mIBO;

    void load() override;
    void unload() override;

    // Apartado 55
    static IndexMesh* generateByRevolution(
        const std::vector<glm::vec2>& profile, GLuint nSamples,
        GLfloat angleMax = 2 * std::numbers::pi);

    static IndexMesh* generateIndexedSphere(GLdouble radius, GLuint nParallels, GLuint nMeridians);

    static IndexMesh* generateIndexedTorus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples);

    // Apartado 59
    static IndexMesh* generateIndexedBox(GLdouble l);
protected:
    void draw() const override;

    // Apartado 62
    void buildNormalVectors();
};

#endif //_H_IndexMesh_H_