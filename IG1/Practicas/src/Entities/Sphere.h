#pragma once

#include "ColorMaterialEntity.h"

// Apartado 64
class Sphere : public ColorMaterialEntity
{
public:
	explicit Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians);
};
