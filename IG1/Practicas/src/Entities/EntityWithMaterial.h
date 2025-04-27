#pragma once

#include "Entity.h"

#include "Material.h"

class EntityWithMaterial : public Abs_Entity 
{
protected:
    Material mMaterial;
public:
    EntityWithMaterial ();
    inline void setMaterial(const Material& m) {mMaterial = m;}

    void render (const glm::mat4& modelViewMat) const override;
};