#pragma once

#include "EntityWithTexture.h"

// Apartado 35
/// @brief Genera una foto según lo que se muestre en la ventana
class Photo: public EntityWithTexture
{
public:
	explicit Photo(Texture* texture, GLdouble w, GLdouble h);
	~Photo();
	void update() override;
private:
};
