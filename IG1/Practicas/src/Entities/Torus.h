#pragma once

#include "ColorMaterialEntity.h"

// Apartado 56
class Torus : public ColorMaterialEntity
{
public:
	explicit Torus(glm::dvec4 color, GLdouble R, GLdouble r, GLuint nPoints = 40, GLuint nSamples = 40);
};
