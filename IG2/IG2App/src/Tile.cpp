#include "Tile.h"

Tile::Tile(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, String mesh, Real fitSize, 
    bool traversable)
: IG2Object(initPos, node, sceneMng, mesh),
traversable(traversable) {
    mNode->_update(true, true);
    Vector3 scale = fitSize / getAABB().getSize();
    scale.y /= 2;
    mNode->setScale(scale);
    mNode->showBoundingBox(true);
}

Tile::Tile(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, Real fitSize, 
    bool traversable)
: IG2Object(initPos, node, sceneMng),
traversable(traversable) {
    mNode->_update(true, true);
    Vector3 scale = fitSize / getAABB().getSize();
    scale.y /= 2;
    mNode->setScale(scale);
    mNode->showBoundingBox(true);
}

bool
Tile::isTraversable() const{
    return traversable;
}