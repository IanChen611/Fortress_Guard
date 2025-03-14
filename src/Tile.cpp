#include "Tile.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"

Tile::Tile(const std::string& ImagePath) {
    LOG_INFO("Tile built");
    SetImage(ImagePath);
}

void Tile::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void Tile::SetTouchable(bool touchable){
    m_Touchable = touchable;
}

void Tile::Update(){
    if(IsMouseInside()){

    }
}


bool Tile::IsMouseInside(){
    glm::vec2 mouse_pos = Util::Input::GetCursorPosition();
    float m_X = m_Transform.translation.x;
    float m_Y = m_Transform.translation.y;
    return (mouse_pos.x >= (m_X - m_Width/2) &&
        mouse_pos.x <= (m_X + m_Width/2) &&
        mouse_pos.y >= (m_Y - m_Height/2) &&
        mouse_pos.y <= (m_Y + m_Height/2));
}