#include "IG2App.h"

#include "IG2Object.h"
#include "Maze.h"
#include "Hero.h"
#include "Enemy.h"

using namespace std;
using namespace Ogre;

IG2App* IG2App::mInstance = nullptr;

IG2App::IG2App() : OgreBites::ApplicationContext("IG2App") {
    if (mInstance == nullptr) {
        mInstance = this;
    }
}

IG2App::~IG2App() {
    if (mInstance == this) {
        mInstance = nullptr;
    }
}

IG2App& 
IG2App::instance() {
    if (mInstance != nullptr)
        return *mInstance;
    else throw std::runtime_error("No existe una instancia de IG2App");
}

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt) {

    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }

    return true;
}


void IG2App::shutdown() {

    for (Enemy *e : mEnemies) {
        if (e != nullptr) delete e;
    }

    mEnemies.clear();

    if (mHero != nullptr) {
        delete mHero;
        mHero = nullptr;
    }

    if (mMaze != nullptr) {
        delete mMaze;
        mMaze = nullptr;
    }

    mShaderGenerator->removeSceneManager(mSM);
    mSM->removeRenderQueueListener(mOverlaySystem);

    mRoot->destroySceneManager(mSM);

    delete mTrayMgr;  mTrayMgr = nullptr;
    delete mCamMgr; mCamMgr = nullptr;

    // do not forget to call the base 
    OgreBites::ApplicationContext::shutdown();
}

void IG2App::setup(void) {

    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);
        
    mSM->addRenderQueueListener(mOverlaySystem);
    //mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", getRenderWindow());
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);

    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void) {

    //------------------------------------------------------------------------
    // Creating the camera

    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);

    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);


    //------------------------------------------------------------------------
    // Creating the light

    //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(-1, -1, -1));
 

    //------------------------------------------------------------------------
    // Creating Sinbad

    //Ogre::Entity* ent = mSM->createEntity("ogrehead.mesh");
    //mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    //mSinbadNode->attachObject(ent);

    // Show bounding box
    //mSinbadNode->showBoundingBox(true);

    mMaze = new Maze(Vector3(0.), mSM->getRootSceneNode()->createChildSceneNode(), mSM, "../stage1.txt", CUBE_SIZE, 
        "cube.mesh", mHero, mEnemies);

    mHero->resetPosition();
    addInputListener(mHero);

    for (Enemy* e : mEnemies) {
        e->resetPosition();
        addInputListener(e);
    }

    // Set position of Sinbad
    //mSinbadNode->setPosition(x, y, z);

    // Set scale of Sinbad
    //mSinbadNode->setScale(1, 1, 1);
    

    //mSinbadNode->yaw(Ogre::Degree(-45));
    //mSinbadNode->setVisible(false);    
}

bool
IG2App::isTileTraversable(int x, int z) const {

    if (mMaze != nullptr) {
        return mMaze->isTileTraversable(x, z);
    }
    else return false;

}

bool
IG2App::isTileTraversable(std::pair<int,int> tile) const {

    if (mMaze != nullptr) {
        return mMaze->isTileTraversable(tile.first, tile.second);
    }
    else return false;

}

Vector3
IG2App::getPosAtTile(int x, int z) const {
    if (mMaze != nullptr) {
        return mMaze->getPosAtTile(x, z);
    }
    else return Vector3(0.);
}

std::pair<int, int>
IG2App::getTileInPos(Vector3 v) const {

    if (mMaze != nullptr) {
        return mMaze->getTileInPos(v);
    }
    else return {0., 0.};
}

bool 
IG2App::checkCollisionTowardsEnemies() const{
    if (mHero != nullptr) {

        AxisAlignedBox hBox = mHero->getAABB();

        for (Enemy *e : mEnemies) 
            if (e != nullptr) 
                if (e->getAABB().intersects(hBox)) 
                    return true;
    }
    
    return false;
}

void
IG2App::restartGame() {
    if (mHero != nullptr) mHero->resetPosition();

    for (Enemy *e : mEnemies) 
        if (e != nullptr) 
            e->resetPosition();
}