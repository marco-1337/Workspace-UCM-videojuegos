#include "Scene.h"

#include <vector>

class CompoundEntity;

class Abs_Entity;

// Apartado 67
class Scene7 : public Scene
{
public:
	void init() override;
    void load() override;
    void unload() override;

    // Apartado 68
    virtual void rotate() override;
	virtual void orbit() override;
private:
    CompoundEntity* inventedNode;
};