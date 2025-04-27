#pragma once

#include "Entity.h"

// Apartado 65
class CompoundEntity : public Abs_Entity
{
public:
    explicit CompoundEntity() {}
    ~CompoundEntity();

    void addEntity(Abs_Entity* aEnt);

    // Apartado 77
    void addLight(PosLight* light);

    void render (const glm::mat4& modelViewMat) const override;
	void update() override;

	void load() override;
	void unload() override;
protected:
    std::vector<Abs_Entity*> gObjects;

    // Apartado 77
    std::vector<PosLight*> gPosLights;
};