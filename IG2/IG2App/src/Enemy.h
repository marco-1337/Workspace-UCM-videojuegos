#pragma once

class Maze;
class Helix;

#include "Character.h"

#include "OgreTimer.h"

enum Direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct RelDir {
    std::pair<int, int> front;
    int oppositeAxisSign;
};

class Enemy: public Character {
public:
    Enemy(SceneNode *node, SceneManager *sceneMng, Real fitSize, Real speed, int tileX, int tileZ, String mainMesh);

    Enemy(SceneNode *node, SceneManager* sceneMng, Real fitSize, Real speed, int tileX, int tileZ, String mainMesh, 
        String firstHelixBladeMesh, Real firstBladeSize, Real firstHelixRadius, 
        int firstHelixAmmount, Real firstHelixRotation, uint64_t firstRotationTime,
        String secondHelixBladeMesh, Real secondBladeSize, Real secondHelixRadius, 
        int secondHelixAmmount, Real secondHelixRotation, uint64_t secondRotationTime);

    virtual ~Enemy();

    void frameRendered(const Ogre::FrameEvent& evt) override;

    virtual void resetPosition() override;

private:

    void calculateDirection();

    Helix  *firstHelix = nullptr;
    Helix  *secondHelix = nullptr;

    Real firstRotation, secondRotation;
    uint64_t firstTimeLimit, secondTimeLimit;
    Timer firstTimer, secondTimer;

    Direction direction = NONE, orientation = UP;

    std::vector<Direction> auxOptions;
};