#include "Money.hpp"

#include "Util/Image.hpp"
#include "Util/Logger.hpp"

Money::Money(int pos_X, int pos_Y, int* player_money){
    m_money_imgpath = RESOURCE_DIR"/Image/UI/money.png";
    m_Transform.translation = glm::vec2(pos_X, pos_Y);
    m_player_money = player_money;
    SetImage(m_money_imgpath);
    SetZIndex(5);
    m_Transform.scale = glm::vec2(0.25f, 0.25f);

    //

}

void Money::Update(){
    
}