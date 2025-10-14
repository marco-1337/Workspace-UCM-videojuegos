#include "Tile.h"

Tile::Tile(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, String mesh, Real fitSize, 
    bool traversable)
: IG2Object(initPos, node, sceneMng, mesh),
traversable(traversable) {
    mNode->_update(true, true);
    mNode->setScale(fitSize / getAABB().getSize());
    mNode->showBoundingBox(true);
}

Tile::Tile(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, Real fitSize, 
    bool traversable)
: IG2Object(initPos, node, sceneMng),
traversable(traversable) {
    mNode->_update(true, true);
    mNode->setScale(fitSize / getAABB().getSize());
    mNode->showBoundingBox(true);
}

bool
Tile::isTraversable() const{
    return traversable;
}