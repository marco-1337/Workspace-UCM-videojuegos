#pragma once

#include "Entity.h"

/// @brief Triangulo plano con las puntas RGB y degradado de color relleno
class RGBTriangle : public EntityWithColors
{
public:
	explicit RGBTriangle(GLdouble r);

	/// @brief Renderiza el triángulo con culling
	/// @param modelViewMat 
	void render(const glm::mat4& modelViewMat) const override;

	/// @brief Gira el triangulo sobre si mismo y lo traslada en un radio
	void update() override;
private:
    /// Guarda el angulo de rotacion para continuar a partir del mismo angulo en cada update
	GLfloat _anguloRotacion = 0.;
};