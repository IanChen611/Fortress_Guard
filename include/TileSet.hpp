#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>
#include <string>

#include "Tile.hpp"

#include "Util/GameObject.hpp"

class TileSet : public Util::GameObject {
public:
    explicit TileSet(const std::vector<Tile>& Tiles);
private:
};

#endif