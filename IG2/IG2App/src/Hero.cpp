#include "Hero.h"
#include "Maze.h"

Hero::Hero(SceneNode *node, SceneManager* sceneMng, String mesh, Real fitSize, Real speed, 
    Maze* maze)
: IG2Object(Vector3(0.), node, sceneMng, mesh),
speed(speed),
tileSize(fitSize),
maze(maze),
dirX(0),
dirZ(0),
tileX(0),
tileZ(0)
{
    halfTileSize = tileSize/2;

    if (maze != nullptr) {
        auto [x, z] = maze->getHeroStartingTile();
        tileX = x;
        tileZ = z;
        mNode->setPosition(maze->getPosAtTile(tileX, tileZ));
    }

    mNode->_update(true, true);
    Vector3 currSize = getAABB().getSize();
    // Evita deformar las entidades
    currSize = Vector3(std::max(currSize.x, currSize.z));
    mNode->setScale(fitSize / currSize);
}

bool
Hero::keyPressed(const OgreBites::KeyboardEvent& evt) {

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
    else return false;

    return true;
}

void 
Hero::frameRendered(const Ogre::FrameEvent& evt) {
    
    if (dirX != 0 || dirZ != 0) {
        if (maze != nullptr) {
            move(evt.timeSinceLastFrame);
        }
    }
}

bool sameSign (Real a, Real b) {
    return (a < 0. && b < 0. ) || (a > 0. && b > 0);
}

void
Hero::move(Real delta) {

    Real finalTraslationX = 0., finalTraslationZ = 0.;
    //Quaternion q = Quaternion(); 

    bool traversable = maze->isTileTraversable(tileX + dirX, tileZ + dirZ);

    Vector3 vectorToDest = Vector3(0.);

    Real distance = std::min(speed * delta, tileSize);

    // Atención, monolito. Siento mucho este horror cósmico, tengo el cerebro plano

    if (!traversable) {
        vectorToDest = maze->getPosAtTile(tileX, tileZ) - getPosition();
        // Si esto se cumple, se está intentando ir al centro de la tile desde fuera
        if (sameSign(dirX, vectorToDest.x) && vectorToDest.z == 0.F) {
            if (std::abs(vectorToDest.x) > distance) vectorToDest.x = distance * dirX;
        }
        else if (sameSign(dirZ, vectorToDest.z) && vectorToDest.x == 0.F) {
            if (std::abs(vectorToDest.z) > distance) vectorToDest.z = distance * dirZ;
        }
    }
    else {
        vectorToDest = maze->getPosAtTile(tileX + dirX, tileZ + dirZ) - getPosition();
        
        if (dirX != 0) {
            if (std::abs(vectorToDest.z) > distance) {
                vectorToDest.z = (vectorToDest.z < 0.) ? -distance : distance;
                vectorToDest.x = 0.;
            } else {
                distance -= std::abs(vectorToDest.z);

                if (distance < std::abs(vectorToDest.x)) vectorToDest.x = distance * dirX;
            }
        }
        else if (dirZ != 0) {
            if (std::abs(vectorToDest.x) > distance) {
                vectorToDest.x = (vectorToDest.x < 0.) ? -distance : distance;
                vectorToDest.z = 0.;
            } else {
                distance -= std::abs(vectorToDest.x);

                if (distance < std::abs(vectorToDest.z)) vectorToDest.z = distance * dirZ;
            }
        }
        
    }

    mNode->translate(vectorToDest);
    auto [x, z] = maze->getTileInPos(getPosition());
    tileX = x;
    tileZ = z;

    dirX = 0;
    dirZ = 0;
}