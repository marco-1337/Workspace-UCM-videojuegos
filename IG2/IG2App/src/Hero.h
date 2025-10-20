#pragma once

#include "Character.h"

class Hero: public Character {
public:
    Hero(SceneNode *node, SceneManager *sceneMng, String mesh, Real fitSize, Real speed, int tileX, int tileZ);

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
    bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
    void frameRendered(const Ogre::FrameEvent& evt) override;
};