#include "Enemy.h"
#include "Helix.h"
#include "IG2App.h"

const std::unordered_map<Direction, RelDir> RELATIVE_DIRECTIONS = {
    {FRONT, {{0, -1}, 1}},
    {BACK, {{0, 1}, 1}},
    {LEFT, {{-1, 0}, -1}},
    {RIGHT, {{1, 0}, -1}}
};

std::pair<int, int>
getRelativeDirection(Direction lookingAt, Direction goingTo) {

    std::pair<int,int> dir = RELATIVE_DIRECTIONS.at(lookingAt).front;
    int mult = RELATIVE_DIRECTIONS.at(lookingAt).oppositeAxisSign;

    switch (goingTo) {
        case FRONT:
            return dir;
            break;
        case LEFT:
            return {dir.second * mult, dir.first * mult};
            break;
        case RIGHT:
            return {-dir.second * mult, -dir.first * mult};
            break;
    }

    return {0, 0};
}

Direction
getOrientationToDir(int x, int z) {
    if (x == 1) return RIGHT;
    if (x == -1) return LEFT;
    if (z == 1) return BACK;
    if (z == -1) return FRONT;

    return NONE;
}

std::pair<int, int>
getRelativeTile(Direction lookingAt, Direction goingTo, int x, int z) {
    std::pair<int,int> dir = getRelativeDirection(lookingAt, goingTo);
    return {dir.first + x, dir.second + z}; 
}



Enemy::Enemy(SceneNode *node, SceneManager* sceneMng, Real fitSize, Real speed, int tileX, int tileZ, String mainMesh)
: Character(node, sceneMng, mainMesh, speed, tileX, tileZ) {
    mNode->_update(true, true);
    Vector3 currSize = getAABB().getSize();
    // Evita deformar las entidades
    currSize = Vector3(std::max(currSize.x, currSize.z));
    mNode->setScale((fitSize / currSize));
}

Enemy::Enemy(SceneNode *node, SceneManager* sceneMng, Real fitSize, Real speed, int tileX, int tileZ, String mainMesh,
    String firstBladeMesh, Real firstBladeSize, Real firstHelixRadius, int firstHelixAmmount, Real firstHelixRotation,
    String secondBladeMesh, Real secondBladeSize, Real secondHelixRadius, int secondHelixAmmount, Real secondHelixRotation)
: Character(node, sceneMng, mainMesh, speed, tileX, tileZ),
firstRotation(firstHelixRotation),
secondRotation(secondHelixRotation) {

    // Obtiene antes el tamaño
    mNode->_update(true, true);
    Vector3 currSize = getAABB().getSize();
    // Evita deformar las entidades
    currSize = Vector3(std::max(currSize.x, currSize.z));
    mNode->setScale((fitSize / currSize));

    firstHelix = new Helix(Vector3(0.), createChildSceneNode(), mSM, 
        firstBladeMesh, firstBladeSize, firstHelixRadius, firstHelixAmmount);
    secondHelix = new Helix(Vector3(0.), createChildSceneNode(), mSM, 
        secondBladeMesh, secondBladeSize, secondHelixRadius, secondHelixAmmount);
}

Enemy::~Enemy() {
    if (firstHelix != nullptr) {
        delete firstHelix;
        firstHelix = nullptr;
    }

    if (secondHelix != nullptr) {
        delete secondHelix;
        secondHelix = nullptr;
    }
}

void 
Enemy::frameRendered(const Ogre::FrameEvent& evt) {
    if (firstHelix != nullptr) firstHelix->roll(Degree(firstRotation * evt.timeSinceLastFrame));
    if (secondHelix != nullptr) secondHelix->roll(Degree(secondRotation * evt.timeSinceLastFrame));

    int x = tileX;
    int z = tileZ;

    Real distance = evt.timeSinceLastFrame * speed;

    // No se tiene dirección, se calcula nueva dirección
    if (direction == NONE) { 
        calculateDirection();
    }
    
    if (direction == BACK) {
        move(distance);
        if (distance > 0.) {
            calculateDirection();
            move(distance);
        }
    }
    else move(distance);

    if (x != tileX || z != tileZ) direction = NONE;
}

void
Enemy::calculateDirection() {
    if (IG2App::instance().isTileTraversable(getRelativeTile(orientation, FRONT, tileX, tileZ))) auxOptions.push_back(FRONT);
    if (IG2App::instance().isTileTraversable(getRelativeTile(orientation, LEFT, tileX, tileZ))) auxOptions.push_back(LEFT);
    if (IG2App::instance().isTileTraversable(getRelativeTile(orientation, RIGHT, tileX, tileZ))) auxOptions.push_back(RIGHT);

    if (auxOptions.empty()) direction = BACK;
    else direction = auxOptions[std::rand() % auxOptions.size()];
    
    // Si tengo que ir hacia atrás primero me estampo, pero si que cambio la orientacion para cuando recalcule
    std::pair<int, int> dir = getRelativeDirection(orientation, (direction == BACK) ? FRONT : direction);
    
    dirX = dir.first;
    dirZ = dir.second;

    // La direccion si que la cambio para cuando deje de estamparse, cuando se recalcule, el nuevo front será el antiguo back
    if (direction == BACK) orientation = getOrientationToDir(-dirX, -dirZ);
    else orientation = getOrientationToDir(dirX, dirZ);

    auxOptions.clear();
}