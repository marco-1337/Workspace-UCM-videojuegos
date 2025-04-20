#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "CompoundEntity.h"

using namespace glm;

CompoundEntity::~CompoundEntity() 
{
    for (Abs_Entity* e : gObjects)
    {
        delete e;
    }

    gObjects.clear();
}

void
CompoundEntity::addEntity(Abs_Entity* aEnt)
{
    gObjects.push_back(aEnt);
}

void
CompoundEntity::load()
{
    for (Abs_Entity* e : gObjects)
    {
        e->load();
    }
}

void
CompoundEntity::unload()
{
    for (Abs_Entity* e : gObjects)
    {
        e->unload();
    }
}

void
CompoundEntity::render(mat4 const& modelViewMat) const
{
    mat4 aMat = modelViewMat * mModelMat;

    for (Abs_Entity* e : gObjects)
    {
        e->render(aMat);
    }
}

void
CompoundEntity::update()
{
    for (Abs_Entity* e : gObjects)
    {
        e->update();
    }
}