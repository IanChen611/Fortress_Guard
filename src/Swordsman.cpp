#include "Swordsman.hpp"
#include "Button.hpp"

#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"

Swordsman::Swordsman() {
    // m_myselfImagePath = RESOURCE_DIR"/output_images/Swordsman/tile_0_0.png";
    SetImage(RESOURCE_DIR"/output_images/Swordsman/tile_0_0.png");
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 10;
    m_attackSpeed = 1;
    m_cost = 15;
    m_rangeCoordinate.push_back({0, 48});
    m_rangeCoordinate.push_back({0, -48});
    m_rangeCoordinate.push_back({-48, 0});
    m_rangeCoordinate.push_back({48, 0});
    for(int _=0; _<4; _++){
        m_rangeTile.push_back(std::make_shared<Tile>(m_rangeImagePath));
    }
    // 升級按鈕
    m_upgradeButton = std::make_shared<Button>(
        RESOURCE_DIR"/Image/UI/upgrade_button.png",
        this->m_Transform.translation.x,
        this->m_Transform.translation.y,
        32, 332,
        1.0f, 1.0f,
        [this]() { 
            this->Upgrade();
        }
    );
    m_upgradeButton->SetZIndex(15);
    m_upgradeButton->SetVisible(false);

    LOG_INFO("Swordsman built");
}

bool Swordsman::IsEnemyInRange(const std::shared_ptr<Enemy> enemy){
    int x = -(((int)enemy->m_Transform.translation.y+240+24)/48-10);
    int y = (((int)enemy->m_Transform.translation.x+480+24)/48);
    int m_x = -(((int)m_coordinate.y+240+24)/48-10);
    int m_y = (((int)m_coordinate.x+480+24)/48);
    return abs(x-m_x) + abs(y-m_y) <= 1;
}

void Swordsman::Update_for_speccial_guard(){
    if(m_attackable && static_cast<int>(m_enemyInRange.size()) >= 1){
        // 為了怕同時造成傷害時，第二次傷害對nullptr造成傷害
        if(m_enemyInRange[0]->GetHealth() > 0){
            m_enemyInRange[0]->GetHurt(m_damage);
        }
        if(m_enemyInRange[0]->IsDead()){
            PopFrontEnemyInRange();
        }
        m_attackable = false;
    }
}

void Swordsman::Upgrade(){
    LOG_INFO("Swordsman upgraded");
    if(m_rank <= 3){
        m_damage += 2;
        m_attackSpeed *= 1.2;
        m_rank += 1;
        LOG_INFO("Swordsman upgraded");
        m_isUpgraded = true;
    }
}