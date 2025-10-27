#pragma once

#include <OgreApplicationContext.h>
#include <OgreSceneManager.h>
#include <OgreRTShaderSystem.h>       
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>
#include "Ogre.h"
#include <OgreWindowEventUtilities.h>
#include <SDL_keycode.h>
#include <memory>

constexpr Ogre::Real SCALE_UNIT = 10.;
constexpr Ogre::Real CUBE_SIZE = 5. * SCALE_UNIT;

constexpr Ogre::Real HERO_SIZE = 6. * SCALE_UNIT;
constexpr Ogre::Real HERO_SPEED = 20. * SCALE_UNIT;

constexpr Ogre::Real ENEMY_SIZE = 4. * SCALE_UNIT;
constexpr Ogre::Real ENEMY_SPEED = 10. * SCALE_UNIT;

constexpr Ogre::Real ENEMY_SWORD_SIZE = 2. * SCALE_UNIT;
constexpr Ogre::Real ENEMY_SWORD_RADIUS = 3.5 * SCALE_UNIT;
constexpr int ENEMY_SWORD_AMMOUNT = 5;
constexpr Ogre::Real ENEMY_SWORD_ROTATION = -90.;
constexpr uint64_t ENEMY_SWORD_ROTATION_TIME = 3500;

constexpr Ogre::Real ENEMY_FISH_SIZE = 1. * SCALE_UNIT;
constexpr Ogre::Real ENEMY_FISH_RADIUS = 4.5 * SCALE_UNIT;
constexpr int ENEMY_FISH_AMMOUNT = 5;
constexpr Ogre::Real ENEMY_FISH_ROTATION = 115.;
constexpr uint64_t ENEMY_FISH_ROTATION_TIME = 4000;

class IG2Object;
class Maze;
class Hero;
class Enemy;

class IG2App: public OgreBites::ApplicationContext, OgreBites::InputListener {

public:

    static IG2App& instance();

    IG2App();
    virtual ~IG2App();

    bool isTileTraversable(int x, int z) const;
    bool isTileTraversable(std::pair<int, int> tile) const;
    Ogre::Vector3 getPosAtTile(int x, int z) const;
    std::pair<int, int> getTileInPos(Ogre::Vector3 v) const;
    bool checkCollisionTowardsEnemies() const;
    void restartGame();
    void updateScoreboard(int lives, int points);

protected:

    static IG2App* mInstance;

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();

    bool dirLight;

    Maze *mMaze = nullptr;
    Hero *mHero = nullptr;
    std::vector<Enemy*> mEnemies;
    OgreBites::TextBox *mScoreboard = nullptr;

    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;

    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;
};
