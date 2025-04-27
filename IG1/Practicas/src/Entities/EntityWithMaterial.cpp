#include "EntityWithMaterial.h"

EntityWithMaterial::EntityWithMaterial () :
mMaterial()
{
    mShader = Shader ::get("light");
}

void
EntityWithMaterial::render(const glm::mat4& modelViewMat) const
{
    if (Abs_Entity::mMesh != nullptr) 
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        mShader->use();
        // Carga los atributos del material en la GPU
        mMaterial.upload(*mShader);
        upload(modelViewMat * mModelMat);
        mMesh->render();
    }
}