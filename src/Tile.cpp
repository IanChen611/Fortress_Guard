#include "Tile.hpp"
#include "Util/Image.hpp"

Tile::Tile(const std::string& ImagePath) {
    SetImage(ImagePath);
}

void Tile::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}