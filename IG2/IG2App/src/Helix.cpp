#include "Helix.h"

Helix::Helix(Vector3 initPos, SceneNode *node, SceneManager *sceneMng, String mesh, Real bladeSize, Real radius, 
    int bladeAmmount)
: IG2Object(initPos, node, sceneMng),
blades() {
    
    Vector3 pos(0, 1., 0);
    pos *= radius;
    Quaternion rotation;
    Real angle = 360./bladeAmmount;
    rotation.FromAngleAxis(Degree(angle), Vector3::UNIT_Z);

    SceneNode* bladeNode = nullptr;
    IG2Object* object = nullptr;

    for (int i = 0; i < bladeAmmount; ++i) {
        bladeNode = createChildSceneNode();
        object = new IG2Object(pos, bladeNode, sceneMng, mesh);
        object->roll(Degree(angle * (i+1)));
        blades.push_back(new IG2Object(pos, bladeNode, sceneMng, mesh));
        pos = rotation * pos;
    }

    if (!blades.empty()) {
        node->_update(true, true);
        Vector3 currSize = blades[0]->getAABB().getSize();

        currSize = Vector3(std::max(currSize.x, currSize.z));
        
        for (IG2Object* b : blades) {
            b->setScale(bladeSize/currSize);
        }
    }
}