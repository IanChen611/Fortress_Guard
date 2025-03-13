#include "Heart.hpp"

#include "Util/Image.hpp"
#include "Util/Logger.hpp"


Heart::Heart(int pos_X, int pos_Y, int index, int* castlehealth_now){
    m_Transform.translation = glm::vec2(pos_X, pos_Y);
    m_index = index;
    m_castlehealth_now = castlehealth_now;
    m_heart_full_imgpath = RESOURCE_DIR"/Image/UI/heart_full.png";
    m_heart_empty_imgpath = RESOURCE_DIR"/Image/UI/heart_empty.png";
    SetImage(m_heart_full_imgpath);
    SetZIndex(5);
    m_Transform.scale = glm::vec2(0.25f, 0.25f);
}

void Heart::Update(){
    // LOG_INFO("Heart Updated");
    if(m_index > *m_castlehealth_now){
        SetImage(m_heart_empty_imgpath);
    }
    if(m_index <= *m_castlehealth_now){
        SetImage(m_heart_full_imgpath);
    }
}

// void Heart::SetImage(const std::string& ImagePath){
//     m_Drawable = std::make_shared<Util::Image>(ImagePath);
// }

