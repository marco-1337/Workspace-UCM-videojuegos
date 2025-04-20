#pragma once

#include "SingleColorEntity.h"

// Apartado 58
class ColorMaterialEntity : public SingleColorEntity
{
public:
	explicit ColorMaterialEntity(glm::dvec4 color = glm::dvec4(0.0, 0.0, 0.0, 1.0));

    // Apartado 61
    static void toggleShowNormals() { ColorMaterialEntity::mShowNormals = !ColorMaterialEntity::mShowNormals;}

	void render(const glm::mat4& modelViewMat) const override;
protected:
    // Apartado 61
    Shader* _normalsShader;
    static GLboolean mShowNormals;
};