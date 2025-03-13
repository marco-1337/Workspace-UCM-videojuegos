#pragma once

#include "SingleColorEntity.h"

// Apartado 4
/// @brief Polígono regular de n vertices, n lados y un plano
class RegularPolygon : public SingleColorEntity 
{
public:
	explicit RegularPolygon(GLuint num, GLdouble r, glm::dvec4 color = glm::dvec4(0.0, 0.0, 0.0, 1.0));
};