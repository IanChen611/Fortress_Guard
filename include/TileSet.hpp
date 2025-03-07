#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>
#include <string>

#include "Tile.hpp"

#include "Util/GameObject.hpp"

class TileSet : public Util::GameObject {
public:
    TileSet(const std::shared_ptr<Tile> tiles[10][20]);

    TileSet() = default;

    ~TileSet() = default;

    void Start();

    void ResetPosition();

    void SetAllZIndex(int zindex);

private:
    std::shared_ptr<Tile> m_tiles[10][20];
};

#endif