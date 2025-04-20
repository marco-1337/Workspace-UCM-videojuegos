#pragma once

#include "ColorMaterialEntity.h"

// Apartado 64
class Disk : public ColorMaterialEntity
{
public:
    explicit Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples);
};