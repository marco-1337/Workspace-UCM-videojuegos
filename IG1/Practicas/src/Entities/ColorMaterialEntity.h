#pragma once

#include "EntityWithMaterial.h"

// Apartado 58
class ColorMaterialEntity : public EntityWithMaterial
{
public:
	explicit ColorMaterialEntity(glm::dvec4 color = glm::dvec4(0.0, 0.0, 0.0, 1.0));

	void render(const glm::mat4& modelViewMat) const override;
protected:
    // Apartado 61
    Shader* _normalsShader;
};