#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "GlassParapet.h"

using namespace glm;

// Apartado 32

GlassParapet::GlassParapet(GLdouble length, Texture* texture, GLboolean modulate)
: BoxOutline(length, texture, nullptr, modulate)
{}

void GlassParapet::render(const glm::mat4& modelViewMat) const 
{
	EntityWithTexture::render(modelViewMat);
}