#pragma once

#include "TranslucentEntity.h"

// Apartado 66
class WingAdvancedTIE: public TranslucentEntity
{
public:
	/// @brief El ala siempre se divide en tres partes verticalmente
	/// @param height 
	/// @param width 
	/// @param wingOffset la distancia de las puntas respecto a la vertical del ala, 0 es igual a un ala sin doblez 
	/// @param texture 
	/// @param modulate 
	explicit WingAdvancedTIE(GLdouble height, GLdouble width, GLdouble wingOffset, 
        Texture* texture, GLboolean modulate = false);
};