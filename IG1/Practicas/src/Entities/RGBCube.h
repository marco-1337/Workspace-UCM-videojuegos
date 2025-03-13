#pragma once

#include "Entity.h"

// Apartado 16
class RGBCube : public EntityWithColors
{
public:
    /// @brief Inicializa el cubo RGB con una esquina alineada con los ejes
    /// @param length 
	explicit RGBCube(GLdouble length);
    
	/// @brief Renderiza mostrando solo las caras externas rellenas
	void render(const glm::mat4& modelViewMat) const override;

    // Apartado 17
    /// @brief Rota el rubo alrededor de los ejes
	void update() override;
private:
    /// Guarda la longitud del cubo para rotar consistentemente sobre los ejes
	GLdouble _length;
    /// Guarda las rotaciones para continuarlas en cada llamada a update
	glm::fvec3 _rotaciones = {0., 0., 0.};
};
