#pragma once

#include "IG2Object.h"
#include <vector>

class Helix: public IG2Object {
public:
    Helix(Vector3 initPos, SceneNode *node, SceneManager *sceneMng, String mesh, Real bladeSize, Real radius, 
        int bladeAmmount);
private:
    std::vector<IG2Object*> blades;
};