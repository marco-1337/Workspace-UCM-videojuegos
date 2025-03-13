#pragma once

#include "EntityWithTexture.h"

// Apartado 23
/// @brief Genera una caja cerrada con una textura interna y externa
class BoxOutline: public EntityWithTexture
{
public:
	/// @brief Construye una caja sin tapa inferior o superior
	/// @param length Longitud de los lados de cada cara
	/// @param texture textura que se ve por fuera de la caja
	/// @param inwardsTexture textura que se ve por dentro de la cada
	/// @param modulate booleano para modular con los colores de la malla
	explicit BoxOutline(GLdouble length, Texture* texture, Texture* inwardsTexture = nullptr, GLboolean modulate = false);
	void render (const glm::mat4& modelViewMat) const override;
protected:
	/// @brief Textura interna
	Texture* mInwardsTexture = nullptr; 
};