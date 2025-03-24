#include "Tile.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"

Tile::Tile(const std::string& ImagePath) {
    m_Transform.scale = {3, 3};

    // LOG_INFO("Tile built");
    SetImage(ImagePath);
    m_Img_Translucent_Gray = std::make_shared<Util::GameObject>();
    std::shared_ptr<Util::Image> img_gray = std::make_shared<Util::Image>(RESOURCE_DIR"/output_images/Tiles/tile_5_22.png");
    m_Img_Translucent_Red = std::make_shared<Util::GameObject>();
    std::shared_ptr<Util::Image> img_red = std::make_shared<Util::Image>(RESOURCE_DIR"/output_images/Tiles/tile_4_22.png");
    
    m_Img_Translucent_Gray->SetZIndex(0);
    m_Img_Translucent_Gray->m_Transform.scale = {3, 3};
    m_Img_Translucent_Red->SetZIndex(2);
    m_Img_Translucent_Red->m_Transform.scale = {3, 3};
    
    // m_Img_Translucent->m_Transform.translation.x = m_Transform.translation.x;
    // m_Img_Translucent->m_Transform.translation.y = m_Transform.translation.y;
    m_Img_Translucent_Gray->SetDrawable(img_gray);
    m_Img_Translucent_Red->SetDrawable(img_red);

    // LOG_INFO("m_Img_Translucent already set image");
}


void Tile::SetPosition(const glm::vec2& Position) { 
    m_Transform.translation = Position;
    m_Img_Translucent_Gray->m_Transform.translation = m_Transform.translation;
    m_Img_Translucent_Red->m_Transform.translation = m_Transform.translation;

}

void Tile::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void Tile::SetTouchable(bool touchable){
    m_Touchable = touchable;
}

void Tile::Update(){
    // LOG_INFO("Tile Updating");
    if(IsMouseInside() && m_Touchable){
        // LOG_INFO("Mouse is inside");
        m_Img_Translucent_Gray->Draw();
    }
    if(IsMouseInside() && !m_Touchable){
        // LOG_INFO("Mouse is inside");
        m_Img_Translucent_Red->Draw();
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