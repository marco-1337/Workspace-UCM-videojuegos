#include "Scene.h"

#include <vector>

class Photo;
class Abs_Entity;

// Apartado 18
/// Escena de texturas
class Scene3 : public Scene
{
public:
	void init() override;
	void load() override;
	void render(Camera const& cam) const override;
private:
	std::vector<Photo*> _photoEntities;
	std::vector<Abs_Entity*> _opaqueEntities;
	std::vector<Abs_Entity*> _translucentEntities;
};