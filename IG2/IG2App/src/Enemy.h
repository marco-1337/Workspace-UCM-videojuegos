#pragma once

class Maze;
class Helix;

#include "Character.h"

enum Direction {
    NONE,
    FRONT,
    BACK,
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
        String firstHelixBladeMesh, Real firstBladeSize, Real firstHelixRadius, int firstHelixAmmount, Real firstHelixRotation, 
        String secondHelixBladeMesh, Real secondBladeSize, Real secondHelixRadius, int secondHelixAmmount, Real secondHelixRotation);

    virtual ~Enemy();

    void frameRendered(const Ogre::FrameEvent& evt) override;

    virtual void resetPosition() override;

private:

    void calculateDirection();

    Helix  *firstHelix = nullptr;
    Helix  *secondHelix = nullptr;

    Real firstRotation, secondRotation;

    Direction direction = NONE, orientation = BACK;

    std::vector<Direction> auxOptions;
};