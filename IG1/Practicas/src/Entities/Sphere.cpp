#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Sphere.h"

#include "IndexMesh.h"

using namespace glm;

//Apartado 64
Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians)
: ColorMaterialEntity()
{
    vector<vec2> profile = vector<vec2>();

    GLdouble angleStep = radians(360.0) / nParallels;

    GLdouble startingPoint = std::numbers::pi/2;

	GLdouble theta = std::numbers::pi / nParallels;

    for (GLuint i = 0; i < nParallels + 1; ++i)
    {
        // Resta para que sea clockwise y los triangulos se pinten en counter-clockwise
		profile.emplace_back((radius * cos(startingPoint - theta * i)), radius * sin(startingPoint- theta * i));
    }

	mMesh = IndexMesh::generateByRevolution(profile, nMeridians);
}