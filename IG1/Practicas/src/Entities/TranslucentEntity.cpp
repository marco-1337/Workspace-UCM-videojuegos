#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "TranslucentEntity.h"

using namespace glm;

TranslucentEntity::TranslucentEntity(Texture* texture, GLboolean modulate)
: EntityWithTexture(texture, modulate)
{}

void
TranslucentEntity::render(const glm::mat4& modelViewMat) const
{
    glDepthMask(GL_FALSE);

        glEnable(GL_BLEND);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            EntityWithTexture::render(modelViewMat);

        glDisable(GL_BLEND);

    glDepthMask(GL_TRUE);
}