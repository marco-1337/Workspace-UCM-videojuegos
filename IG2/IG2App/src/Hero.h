#pragma once

#include "IG2Object.h"
#include <memory>

class Maze;

class Hero: public IG2Object {
public:
    Hero(SceneNode *node, SceneManager* sceneMng, String mesh, Real fitSize, Real speed,
        Maze* maze);

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
    //bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
    void frameRendered(const Ogre::FrameEvent& evt) override;
private:
    int tileX, tileZ;
    int dirX, dirZ;
    Real speed, tileSize, halfTileSize;
    Maze* maze;

    void move(Real delta);
};