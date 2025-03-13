#pragma once

#include "Entity.h"

/// @brief Entidad renderizable con un color único
class SingleColorEntity : public Abs_Entity
{
public:
	explicit SingleColorEntity(glm::dvec4 color = glm::dvec4(0.0, 0.0, 0.0, 1.0));
	glm::dvec4 color() const;

	/// @brief Asigna un color a la entidad
	/// @param color color a asignar
	void setColor(glm::dvec4 color);

	/// @brief Renderiza usando el color asignado
	/// @param modelViewMat matriz de vista¿?
	void render(const glm::mat4& modelViewMat) const override;

protected:
	glm::dvec4 mColor;
};