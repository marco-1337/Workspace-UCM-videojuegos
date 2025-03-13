#pragma once

#include "Entity.h"

// Apartado 19
/// @brief Cualquier entidad con textura debe de heredar de esta clase
class EntityWithTexture: public Abs_Entity
{
protected:
	/// @brief Textura principal
	Texture* mTexture = nullptr;
	GLboolean mModulate; // indica si modulará la textura con el color de los vértices
public:
	explicit EntityWithTexture(Texture* texture, GLboolean modulate = false);
	void render (const glm::mat4& modelViewMat) const override;
};