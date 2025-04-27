#pragma once

#include "ColorMaterialEntity.h"

// Apartado 64
class Cone : public ColorMaterialEntity
{
public:
    explicit Cone(glm::dvec4 color, GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples);
};