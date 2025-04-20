#pragma once

#include "ColorMaterialEntity.h"

// Apartado 64
class Cone : public ColorMaterialEntity
{
public:
    explicit Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples);
};