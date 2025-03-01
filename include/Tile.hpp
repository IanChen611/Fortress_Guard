#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <string>

#include "Util/GameObject.hpp"

class Tile : public Util::GameObject {
public:
    explicit Tile(const std::string& tilesetPath);

private:
};

#endif