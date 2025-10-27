#include "Hero.h"
#include "IG2App.h"
#include <iostream>

Hero::Hero(SceneNode *node, SceneManager *sceneMng, String mesh, Real fitSize, Real speed, int tileX, int tileZ)
: Character(node, sceneMng, mesh, speed, tileX, tileZ) {
    mNode->_update(true, true);
    Vector3 currSize = getAABB().getSize();
    currSize = Vector3(std::max(currSize.x, currSize.z));
    mNode->setScale((fitSize / currSize));
}

bool
Hero::keyPressed(const OgreBites::KeyboardEvent& evt) {

    if (evt.repeat == 0) {
        if (evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_DOWN) {
            dirX = 0;
            if (dirZ == 0) {
                if (evt.keysym.sym == SDLK_UP) dirZ = -1;
                else dirZ = 1;
            }
        }
        else if (evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_RIGHT) {
            dirZ = 0;
            if (dirX == 0) {
                if (evt.keysym.sym == SDLK_RIGHT) dirX = 1;
                else dirX = -1;
            }
        }
        else if (evt.keysym.sym == SDLK_l && lightNode != nullptr) {
            lightEnabled = !lightEnabled;
            lightNode->setVisible(lightEnabled);
        }

        else return false;

        return true;
    }

    return false;
}

bool
Hero::keyReleased(const OgreBites::KeyboardEvent& evt) {
    if (evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_DOWN || 
        evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_RIGHT) {

        dirX = 0;
        dirZ = 0;

        return true;
    }

    return false;
}

void 
Hero::frameRendered(const Ogre::FrameEvent& evt) {
    
    if (dirX != 0 || dirZ != 0) {
        Real dist = evt.timeSinceLastFrame * speed;
        move(dist);
    }

    if (IG2App::instance().checkCollisionTowardsEnemies()) hurt();
}

void
Hero::hurt() {
    if (--lives <= 0) {
        lives = 3;
        IG2App::instance().restartGame();
    }
    else resetPosition();

    IG2App::instance().updateScoreboard(lives, 0);
}