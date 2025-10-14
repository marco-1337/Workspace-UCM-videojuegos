#pragma once

#include "IG2Object.h"

class Tile: public IG2Object {
public:

    Tile() = default;

    Tile(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, String mesh, Real fitSize, 
        bool traversable = false);

    Tile(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, Real fitSize, 
        bool traversable = true);

    bool isTraversable() const;
private:
    bool traversable;
};