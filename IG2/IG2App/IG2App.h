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
constexpr Ogre::Real HERO_SPEED = 20. * SCALE_UNIT;

class IG2Object;
class Maze;
class Hero;

class IG2App: public OgreBites::ApplicationContext, OgreBites::InputListener {

public:

    explicit IG2App() : OgreBites::ApplicationContext("IG2App") {};
    virtual ~IG2App() {};

protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();


    Ogre::SceneNode* mSinbadNode = nullptr;

    Maze* mMaze = nullptr;

    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;

    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;
};
