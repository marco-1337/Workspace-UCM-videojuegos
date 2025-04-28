#include "Scene.h"

#include <vector>

class CompoundEntity;
class Abs_Entity;
class PosLight;

// Apartado 67
class Scene7 : public Scene
{
public:
	void init() override;
    void load() override;
    void unload() override;

    GLboolean sceneKeyPress(GLchar) override;
private:

    CompoundEntity* tieInventedNode;

    PosLight* posLight = nullptr;
    SpotLight* spotLight = nullptr;
    SpotLight* tieLight = nullptr;

    // Apartado 68
    void rotate();
	void orbit();
};