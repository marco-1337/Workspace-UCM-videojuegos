#include "Maze.h"
#include "IG2App.h"
#include "Tile.h"
#include "Hero.h"

#include <fstream>

Maze::Maze(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, const String& srcFile, Real tileSize, 
    const String& tileMesh) 
: IG2Object(initPos, node, sceneMng),
tileSize(tileSize),
heroStartRow(0),
heroStartCol(0) {
    buildMaze(srcFile, tileMesh);
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

    if (hero != nullptr) {
        delete hero;
        hero = nullptr;
    }
}

void
Maze::buildMaze(const String& srcFile, const String& tileMesh) {

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

    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {

            mazeFile >> tile;

            if (tile == 'x') {
                mazeNodes[i][j] = new Tile(Vector3(xPos, initialPosition.y, zPos), createChildSceneNode(), mSM,
                    tileMesh, tileSize);
            }
            else {
                mazeNodes[i][j] = new Tile(Vector3(xPos, initialPosition.y, zPos), createChildSceneNode(), mSM,
                    tileSize);
                
                if (tile == 'h') {
                    heroStartRow = i;
                    heroStartCol = j;
                    hero = new Hero(createChildSceneNode(), mSM, "Sinbad.mesh", CUBE_SIZE, HERO_SPEED, this);
                }
            }
            xPos += tileSize;
        } 
        xPos = startX;
        zPos += tileSize;
    }

    mazeFile.close();
}

bool
Maze::isTileTraversable(int x, int z) const {

    if (x < 0 || z < 0 || z > mazeNodes.size() || x > mazeNodes[0].size()) {
        return true;
    }

    // Invertido porque maznodes esta dispuesto en [rows][cols]
    return mazeNodes[z][x]->isTraversable();
}

Vector3
Maze::getPosAtTile(int x, int z) const {
    return mazeNodes[z][x]->getPosition();
}

const std::pair<int, int>&
Maze::getHeroStartingTile() const {
    return {heroStartCol, heroStartRow};
}

const std::pair<int, int>& 
Maze::getTileInPos(Vector3 v) const {

    Vector3 originPos = mazeNodes[0][0]->getPosition();

    originPos.x -= tileSize/2.;
    originPos.z -= tileSize/2.;

    v = v - originPos;
    return {v.x / tileSize, v.z /tileSize};
}

Real
Maze::getTileSize() const {
    return tileSize;
}

Hero*
Maze::getHero() const {
    return hero;
}