#pragma once

#include "ColorMaterialEntity.h"

// Apartado 64
class Disk : public ColorMaterialEntity
{
public:
    explicit Disk(glm::dvec4 color, GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples);
};