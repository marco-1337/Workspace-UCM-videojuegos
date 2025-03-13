#pragma once

#include "EntityWithTexture.h"

// Apartado 27
/// @brief Plano con forma de estrella con su centro desplazado formando un pico
class Star3D: public EntityWithTexture
{
public:
	/// @brief 
	/// @param re Longitud desde el centro de la zona de la estrella a las puntas mallores
	/// @param np Número de puntas
	/// @param h Distancia del plano de la estrella al origen
	/// @param texture 
	/// @param modulate 
	explicit Star3D(GLdouble re, GLuint np, GLdouble h, Texture* texture, GLboolean modulate = false);

	/// @brief Renderiza la estrella haciendo un espejo de la misma
	/// @param modelViewMat 
	void render (const glm::mat4& modelViewMat) const override;
	
    // Apartado 28
	/// @brief rota la estrella con el eje en su primer punto y sobre la normal del plano de la estrella
	void update() override;
private:

    // Guarda las rotaciones en cada eje para continuarlas en cada frame del update

	GLfloat _yRotation = 0.0;
	GLfloat _zRotation = 0.0;
	static constexpr GLfloat ROTATION_SPEED = 0.05;
};