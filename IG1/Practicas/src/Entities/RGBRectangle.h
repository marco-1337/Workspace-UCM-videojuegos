#pragma once

#include "Entity.h"

/// @brief Rectangulo RGB, como en RGBTriangle
class RGBRectangle : public EntityWithColors
{
public:
	explicit RGBRectangle(GLdouble w, GLdouble h);
	void render(const glm::mat4& modelViewMat) const override;
};