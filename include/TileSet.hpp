#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>
#include <string>

#include "Tile.hpp"

#include "Util/GameObject.hpp"

class TileSet : public Util::GameObject {
public:
    explicit TileSet(const Tile Tiles[10][20]);

    void Start();

    void ResetPosition();

private:
    Tile m_Tiles[10][20];
};

#endif