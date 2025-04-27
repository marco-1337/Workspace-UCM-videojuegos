#pragma once

#include "ColorMaterialEntity.h"

// Apartado 64
class Sphere : public ColorMaterialEntity
{
public:
	explicit Sphere(glm::dvec4 color, GLdouble radius, GLuint nParallels, GLuint nMeridians);
};
