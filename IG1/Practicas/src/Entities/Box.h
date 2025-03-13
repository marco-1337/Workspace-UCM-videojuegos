#pragma once

#include "BoxOutline.h"

// Apartado 30
class Box: public BoxOutline
{
public:
	explicit Box(GLdouble length, Texture* texture, Texture* inwardsTexture, GLboolean modulate = false);
	~Box();

	/// @brief Añade el renderizado de la tapa y la parte interior
	void render (const glm::mat4& modelViewMat) const override;
	/// @brief Abre y cierra la tapa
	void update() override;

	/// @brief Override al load para cargar la mesh de tapa y fondo
	void load() override;
    /// @brief Override al load para descargar la mesh de tapa y fondo
	void unload() override;

	/// @brief Hace override a setBaseMat porque debe actualizar la matriz de top y bottom
	void setBaseMat(glm::mat4& newMat) override;
private:
	/// Longitud de la caja
	GLdouble _length;
	/// Direccion en la que se está abriendo la caja
	GLint _dir = -1;
	/// Ángulo de apertura
	GLfloat _openAngle = 0.0;
    /// Mesh para la parte de arriba y abajo de la caja (son la misma)
	Mesh* mTopMesh;
    /// Matriz de modelado para la parte de abajo de la caja
	glm::mat4 mBottomModelMat;
    /// Matriz de modelado para la tapa
	glm::mat4 mTopModelMat;

	static constexpr GLfloat OPEN_ANGLE_SPEED = 0.05;
};