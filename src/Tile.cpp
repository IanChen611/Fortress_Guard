#include "Tile.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

Tile::Tile(const std::string& ImagePath) {
    LOG_INFO("Tile built");
    SetImage(ImagePath);
    LOG_INFO("Tile's image already set.");
}

void Tile::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}