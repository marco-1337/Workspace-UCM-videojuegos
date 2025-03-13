#pragma once

#include "SingleColorEntity.h"

// Apartado 15
/// @brief Cubo de un solo color usando GL Triangles
class Cube : public SingleColorEntity
{
public:
	explicit Cube(GLdouble length);
	/// @brief Renderiza el cubo con culling
	void render(const glm::mat4& modelViewMat) const override;
};
