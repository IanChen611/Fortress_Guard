#include "Swordsman.hpp"
#include "Level.hpp"

#include "Util/Logger.hpp"

Swordsman::Swordsman(Level* level) {
    m_level = level;
    // m_myselfImagePath = RESOURCE_DIR"/output_images/Swordsman/tile_0_0.png";
    SetImage(RESOURCE_DIR"/output_images/Swordsman/tile_0_0.png");
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 18;
    m_attackSpeed = 1.5;
    m_cost = 15;
    m_rangeCoordinate.push_back({0, 48});
    m_rangeCoordinate.push_back({0, -48});
    m_rangeCoordinate.push_back({-48, 0});
    m_rangeCoordinate.push_back({48, 0});
    for(int _=0; _<4; _++){
        m_rangeTile.push_back(std::make_shared<Tile>(m_rangeImagePath));
    }
    // // 升級按鈕
    // m_upgradeButton = std::make_shared<Button>(
    //     RESOURCE_DIR"/Image/UI/upgrade_button.png",
    //     this->m_Transform.translation.x,
    //     this->m_Transform.translation.y,
    //     32, 32,
    //     1.0f, 1.0f,
    //     [this]() { 
    //         this->Upgrade();
    //     }
    // );
    // m_upgradeButton->SetZIndex(15);
    // m_upgradeButton->SetVisible(false);

    // 升級花費
    // m_upgradeCost = std::make_shared<Util::GameObject>();
    // m_upgradeCost->SetZIndex(15);
    // m_upgradeCost->SetVisible(false);
    // m_upgradeCost_text = std::make_shared<Util::Text>(
    //     RESOURCE_DIR"/Font/Inter.ttf",
    //     15, std::to_string(10),
    //     Util::Color(254, 254, 0));
    // m_upgradeCost->SetDrawable(m_upgradeCost_text);

    //等級UI
    // m_ranknumber = std::make_shared<Util::GameObject>();
    // m_ranknumber->SetZIndex(15);
    // m_ranknumber->SetVisible(false);
    // m_ranknumber_text = std::make_shared<Util::Text>(
    //     RESOURCE_DIR"/Font/Inter.ttf",
    //     16, std::to_string(m_rank),
    //     Util::Color(0, 0, 0));
    // m_ranknumber->SetDrawable(m_ranknumber_text);
    
    // 讀取動畫圖
    for(int i=0;i<=3;i++){
        attackdown.push_back(RESOURCE_DIR"/output_images/Swordsman/tile_4_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        attackup.push_back(RESOURCE_DIR"/output_images/Swordsman/tile_5_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        attackright.push_back(RESOURCE_DIR"/output_images/Swordsman/tile_6_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        attackleft.push_back(RESOURCE_DIR"/output_images/Swordsman/tile_7_" + std::to_string(i) +".png");
    }


    
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
    if(m_attackable && static_cast<int>(m_enemyInRange.size() && !attacking) >= 1){
        // 動畫開始
        attacking = true;
        // 為了怕同時造成傷害時，第二次傷害對nullptr造成傷害
        if(m_enemyInRange[0]->GetHealth() > 0){
            m_enemyInRange[0]->GetHurt(m_damage);
            // 找動畫方向
            attack_direction = FindDirectionofFirstEnemy(m_enemyInRange[0]);
        }
        if(m_enemyInRange[0]->IsDead()){
            PopFrontEnemyInRange();
        }
        m_attackable = false;
    }
    // 動畫更新
    if(attacking){
        // LOG_INFO("Now Pictuce is " + std::to_string(now_picture));
        if(attack_direction == "right"){
            SetImage(attackright[now_picture]);
        }
        else if(attack_direction == "left"){
            SetImage(attackleft[now_picture]);
        }
        else if(attack_direction == "up"){
            SetImage(attackup[now_picture]);
        }
        else if(attack_direction == "down"){
            SetImage(attackdown[now_picture]);
        }
        picture_interval += 1;
        if(picture_interval > 3){
            now_picture += 1;
            picture_interval = 0;
        }
        if(now_picture >= 4){
            attacking = false;
            now_picture = 0;
            SetImage(RESOURCE_DIR"/output_images/Swordsman/tile_0_0.png");
            // LOG_INFO("Set origin picture");
        }
    } 
}

void Swordsman::Upgrade(){
    if(m_rank < m_maxrank && m_level->m_player_money_now >= 10*m_rank + (m_rank - 3)*(m_rank - 2)*(m_rank - 1)){
        m_damage += 5;
        m_attackSpeed *= 1.2;
        m_level->m_player_money_now -= 10*m_rank + (m_rank - 3)*(m_rank - 2)*(m_rank - 1);
        m_rank += 1;
        LOG_INFO("Swordsman upgraded");
    }
    else{
        LOG_INFO("upgrade fail");
    }
}
