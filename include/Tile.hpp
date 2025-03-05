#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <string>

#include "Util/GameObject.hpp"

class Tile : public Util::GameObject {
public:
    Tile(const std::string& ImagePath);

    ~Tile() = default;

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

private:
    std::string m_ImagePath;
};

#endif