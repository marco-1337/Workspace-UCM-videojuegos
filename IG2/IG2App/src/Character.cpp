#include "Character.h"
#include "IG2App.h"

Character::Character(SceneNode *node, SceneManager* sceneMng, String mesh, Real speed, int tileX, int tileZ)
: IG2Object(Vector3(0.), node, sceneMng, mesh),
speed(speed),
dirX(0),
dirZ(0),
tileX(tileX),
tileZ(tileZ),
startingTileX(tileX),
startingTileZ(tileZ)
{
    halfTileSize = tileSize/2;

    mNode->setPosition(IG2App::instance().getPosAtTile(tileX, tileZ));
}

Character::~Character() {
    deleteLight();
}

bool sameSign (Real a, Real b) {
    return (a < 0. && b < 0. ) || (a > 0. && b > 0);
}

void
Character::resetPosition() {

    dirX = 0;
    dirZ = 0;
    
    tileX = startingTileX;
    tileZ = startingTileZ;
    
    setPosition(IG2App::instance().getPosAtTile(tileX, tileZ));
    mNode->rotate(getOrientation().getRotationTo(Vector3(0., 0., 1.)));
}

void 
Character::addPointlight(Vector3 position, float r, float g, float b) {
    
    deleteLight();
    
    light = mSM->createLight("PointLightHero");
    light->setType(Light::LT_POINT);
    light->setDiffuseColour(r, g, b);

    lightNode = createChildSceneNode();
    lightNode->setPosition(position);
    lightNode->attachObject(light);
}

void 
Character::addSpotlight(Vector3 position, float r, float g, float b, Vector3 direction, 
    Degree innerAngle, Degree outerAngle, float falloff) {
    
    deleteLight();

    light = mSM->createLight("SpotLight");
    light->setType(Light::LT_SPOTLIGHT);
    light->setSpotlightInnerAngle(innerAngle);
    light->setSpotlightOuterAngle(outerAngle);
    light->setSpotlightFalloff(falloff);
    light->setDiffuseColour(r, g, b);

    lightNode = createChildSceneNode();
    lightNode->setPosition(position);
    lightNode->setDirection(direction);
    lightNode->attachObject(light);
}

void
Character::deleteLight() {
    if (light != nullptr) {
        mSM->destroyEntity(light);
        light = nullptr;
    }

    if (lightNode != nullptr) {
        mSM->destroySceneNode(lightNode);
        lightNode = nullptr;
    }
}

void
Character::move(Real& distance) {

    bool traversable = IG2App::instance().isTileTraversable(tileX + dirX, tileZ + dirZ);

    Vector3 vectorToDest = Vector3(0.);
    Real originDistance = distance;

    // Atención, monolito de código

    if (!traversable) {
        vectorToDest = IG2App::instance().getPosAtTile(tileX, tileZ) - getPosition();
        // Si esto se cumple, se está intentando ir al centro de la tile desde fuera
        if (sameSign(dirX, vectorToDest.x) && vectorToDest.z == 0.F) {
            if (std::abs(vectorToDest.x) > distance) vectorToDest.x = distance * dirX;
        }
        else if (sameSign(dirZ, vectorToDest.z) && vectorToDest.x == 0.F) {
            if (std::abs(vectorToDest.z) > distance) vectorToDest.z = distance * dirZ;
        }
        else vectorToDest = Vector3(0.);
    }
    else {
        vectorToDest = IG2App::instance().getPosAtTile(tileX + dirX, tileZ + dirZ) - getPosition();
        
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

    distance = originDistance - std::abs(vectorToDest.x) - std::abs(vectorToDest.z); 
    mNode->translate(vectorToDest);
    auto [x, z] = IG2App::instance().getTileInPos(getPosition());
    tileX = x;
    tileZ = z;

    Quaternion q = Quaternion();
    if ((vectorToDest.x == 0. && vectorToDest.z != 0. && dirX != 0) || (vectorToDest.z == 0. && vectorToDest.x != 0. && dirZ != 0)) {
        q = getOrientation().getRotationTo(vectorToDest);
    } else {
        q = getOrientation().getRotationTo(Vector3(dirX, 0., dirZ));
    }

    mNode->rotate(q);
}