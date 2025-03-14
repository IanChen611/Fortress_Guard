#include "Money.hpp"

#include "Util/Text.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

Money::Money(int pos_X, int pos_Y, int* player_money){
    m_money_imgpath = RESOURCE_DIR"/Image/UI/money.png";
    m_Transform.translation = glm::vec2(pos_X, pos_Y);
    m_player_money = player_money;
    SetImage(m_money_imgpath);
    SetZIndex(5);
    m_Transform.scale = glm::vec2(0.25f,0.25f);

    //
    // 字體檔：/Font/Inter.ttf
    m_number = std::make_shared<Ui>();
    m_number_text = std::make_shared<Util::Text>(
        RESOURCE_DIR"/Font/Inter.ttf",
        140, std::to_string(*m_player_money),
        Util::Color(127, 127, 127));
    m_number->SetZIndex(5);
    m_number->m_Transform.scale = glm::vec2(0.25f, 0.25f);
    m_number->m_Transform.translation = {pos_X + 60, pos_Y};
    // LOG_INFO("Test for Money built");
    m_number->SetDrawable(m_number_text);
}


void Money::Update(){
    m_number_text->SetText(std::to_string(*m_player_money));
    m_number->Draw();
}
