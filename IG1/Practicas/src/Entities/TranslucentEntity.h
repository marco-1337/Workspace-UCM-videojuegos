#pragma once

#include "EntityWithTexture.h"

class TranslucentEntity: public EntityWithTexture
{
public:
	explicit TranslucentEntity(Texture* texture, GLboolean modulate = false);
	void render (const glm::mat4& modelViewMat) const override;
};