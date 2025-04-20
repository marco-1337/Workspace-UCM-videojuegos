#include "Scene.h"

#include <vector>

class Abs_Entity;

// Apartado 66
class Scene6 : public Scene
{
public:
	void init() override;
	void load() override;
    void unload() override;
};