#pragma once

#include <vector>
#include "IG2Object.h"

class Tile;
class Hero;
class Enemy;

class Maze: public IG2Object {
public:
    Maze(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, const String& srcFile, Real tileSize,
        const String& tileMesh, Hero*& hero, std::vector<Enemy*>& enemies);
    ~Maze();

    bool isTileTraversable(int x, int z) const;
    Vector3 getPosAtTile(int x, int z) const;
    std::pair<int, int> getTileInPos(Vector3 v) const;

private:
    void buildMaze(const String& srcFile, const String& tileMesh, Hero*& hero, std::vector<Enemy*>& enemies);
    Real tileSize;
    std::vector<std::vector<Tile*>> mazeNodes;
};