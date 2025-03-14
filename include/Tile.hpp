#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <string>

#include "Util/GameObject.hpp"
#include "Util/Input.hpp"

class Tile : public Util::GameObject {
public:
    Tile(const std::string& ImagePath);

    Tile() = default;

    ~Tile() = default;

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetTouchable(bool touchable);
    
    void Update();

    bool IsMouseInside();

private:
    std::string m_ImagePath;
    bool m_Touchable = false;
    float m_Width = 48.0f;
    float m_Height = 48.0f;
};

#endif