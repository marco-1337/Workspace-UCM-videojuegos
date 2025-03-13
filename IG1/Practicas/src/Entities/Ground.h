#pragma once

#include "EntityWithTexture.h"

// Apartado 18
/// @brief Plano cuadrado con una textura
class Ground: public EntityWithTexture
{
public:
	explicit Ground(GLdouble w, GLdouble h, Texture* texture, GLboolean modulate = false, GLint rw = 1, GLint rh = 1);
};