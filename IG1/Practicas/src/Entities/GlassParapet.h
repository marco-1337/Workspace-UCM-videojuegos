#pragma once

#include "BoxOutline.h"

/// @brief Basicamente es un BoxOutline pero sin culling ni textura extra
class GlassParapet: public BoxOutline
{
public:
	explicit GlassParapet(GLdouble length, Texture* texture, GLboolean modulate = false);
	void render(const glm::mat4& modelViewMat) const override;
private:
};