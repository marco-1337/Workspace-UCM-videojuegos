#include "Maze.h"
#include "IG2App.h"
#include "Tile.h"
#include "Hero.h"
#include "Enemy.h"

#include <fstream>

Maze::Maze(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, const String& srcFile, Real tileSize, 
    const String& tileMesh, Hero*& hero, std::vector<Enemy*>& enemies) 
: IG2Object(initPos, node, sceneMng),
tileSize(tileSize) {
    hero = nullptr;
    enemies = std::vector<Enemy*>();
    buildMaze(srcFile, tileMesh, hero, enemies);
}

Maze::~Maze() {
    for (std::vector<Tile*>& row : mazeNodes) {
        for (Tile* t : row) {
            if (t != nullptr) {
                delete t;
            }
        }
        row.clear();
    }
    mazeNodes.clear();

    if (floor != nullptr) {
        delete floor;
        floor = nullptr;
    }
}

void
Maze::buildMaze(const String& srcFile, const String& tileMesh, Hero*& hero, std::vector<Enemy*>& enemies) {

    std::ifstream mazeFile(srcFile);

    if (mazeFile.fail()) throw std::runtime_error(srcFile + " not found");

    Vector3 initPos = getPosition();

    int nCols, nRows;
    mazeFile >> nCols >> nRows;

    mazeNodes = std::vector<std::vector<Tile*>>(nRows, std::vector<Tile*>(nCols, nullptr));

    Real startX = initPos.x - (nCols / 2 * CUBE_SIZE);
    Real startZ = initPos.z - (nRows / 2 * CUBE_SIZE);

    if (nCols % 2 == 0) {
        startX += CUBE_SIZE / 2;
    }

    if (nRows % 2 == 0) {
        startZ += CUBE_SIZE / 2;
    }

    Real    xPos = startX, 
            zPos = startZ;
    char tile;

    // Bool de control para que minimo se genere un enemigo con mas mallas y movidas
    bool min = false;

    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {

            mazeFile >> tile;

            if (tile == 'x') {
                mazeNodes[i][j] = new Tile(Vector3(xPos, initialPosition.y, zPos), createChildSceneNode(), mSM, tileMesh, tileSize);
            }
            else {
                mazeNodes[i][j] = new Tile(Vector3(xPos, initialPosition.y, zPos), createChildSceneNode(), mSM, tileSize);
                 
                if (tile == 'h') {
                    hero = new Hero(createChildSceneNode(), mSM, "Sinbad.mesh", HERO_SIZE, HERO_SPEED, j, i);
                }
                else if (tile == 'v') {
                    if (std::rand() % 2 == 0 && min) {
                        enemies.push_back(new Enemy(createChildSceneNode(), mSM, ENEMY_SIZE, ENEMY_SPEED, j, i, "ogrehead.mesh")); 
                    }
                    else {
                        enemies.push_back(new Enemy(createChildSceneNode(), mSM, ENEMY_SIZE, ENEMY_SPEED, j, i, "ogrehead.mesh", 
                            "Sword.mesh", ENEMY_SWORD_SIZE, ENEMY_SWORD_RADIUS, ENEMY_SWORD_AMMOUNT, ENEMY_SWORD_ROTATION,
                            "fish.mesh", ENEMY_FISH_SIZE, ENEMY_FISH_RADIUS, ENEMY_FISH_AMMOUNT, ENEMY_FISH_ROTATION));
                        min = true;
                    }
                }
            }
            xPos += tileSize;
        } 
        xPos = startX;
        zPos += tileSize;
    }

    mazeFile.close();

    MeshManager::getSingleton().createPlane("mMazePlane",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        nCols*tileSize*1.2, nRows*tileSize*1.2, nCols, nRows,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);
    
    floor = new IG2Object(Vector3(0., -tileSize, 0.), createChildSceneNode(), mSM, "mMazePlane");
}

bool
Maze::isTileTraversable(int x, int z) const {

    if (x < 0 || z < 0 || z >= mazeNodes.size() || x >= mazeNodes[0].size()) {
        return true;
    }

    // Invertido porque maznodes esta dispuesto en [rows][cols]
    return mazeNodes[z][x]->isTraversable();
}

Vector3
Maze::getPosAtTile(int x, int z) const {
    return mazeNodes[z][x]->getPosition();
}

std::pair<int, int>
Maze::getTileInPos(Vector3 v) const {

    Vector3 originPos = mazeNodes[0][0]->getPosition();

    originPos.x -= tileSize/Real(2.);
    originPos.z -= tileSize/Real(2.);

    v = v - originPos;
    return {v.x / tileSize, v.z /tileSize};
}