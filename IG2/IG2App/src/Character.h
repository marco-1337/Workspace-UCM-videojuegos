#pragma once

class IG2App;

#include "IG2Object.h"

class Character: public IG2Object {
public:
    Character(SceneNode *node, SceneManager* sceneMng, String mesh, Real speed, int tileX, int tileZ);

    void resetPosition();
protected:
    int tileX, tileZ,
        startingTileX, startingTileZ;

    // Las direcciones deben ser 0, 1 o -1. Si una es != 0 la otra debe de ser 0 
    int dirX, dirZ;
    Real speed, tileSize, halfTileSize;

    // devuelve la distancia sobrante
    void move(Real& distance);
};