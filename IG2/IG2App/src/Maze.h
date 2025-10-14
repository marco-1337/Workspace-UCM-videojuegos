#pragma once

#include <vector>
#include "IG2Object.h"

class Tile;
class Hero;

class Maze: public IG2Object {
public:
    Maze(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, const String& srcFile, Real tileSize,
        const String& tileMesh);
    ~Maze();

    bool isTileTraversable(int x, int z) const;

    // no se por que pasa, pero si pasas esto como referencia el punto flotante, los 0. se los carga y se convierten en yo quese
    Vector3 getPosAtTile(int x, int z) const;
    const std::pair<int, int>& getHeroStartingTile() const;
    const std::pair<int, int>& getTileInPos(Vector3 v) const;
    Real getTileSize() const;
    Hero* getHero() const;
    
private:
    void buildMaze(const String& srcFile, const String& tileMesh);
    Real tileSize;
    int heroStartRow, heroStartCol;
    std::vector<std::vector<Tile*>> mazeNodes;
    Hero* hero;
};