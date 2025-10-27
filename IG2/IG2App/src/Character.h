#pragma once

class IG2App;

#include "IG2Object.h"

class Character: public IG2Object {
public:
    Character(SceneNode *node, SceneManager* sceneMng, String mesh, Real speed, int tileX, int tileZ);
    ~Character();

    virtual void resetPosition();

    void addPointlight(Vector3 position, float r, float g, float b);
    void addSpotlight(Vector3 position, float r, float g, float b, Vector3 direction, 
        Degree innerAngle, Degree outerAngle, float falloff);

protected:
    int tileX, tileZ,
        startingTileX, startingTileZ;

    // Las direcciones deben ser 0, 1 o -1. Si una es != 0 la otra debe de ser 0 
    int dirX, dirZ;
    Real speed, tileSize, halfTileSize;

    // devuelve la distancia sobrante
    void move(Real& distance);

    void deleteLight();

    Light *light = nullptr;
    SceneNode *lightNode = nullptr;
    bool lightEnabled = true;
};