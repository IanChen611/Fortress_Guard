#include "Musketeer.hpp"
#include "Level.hpp"

#include "Util/Logger.hpp"

Musketeer::Musketeer(Level* level){
    m_level = level;
    SetImage(RESOURCE_DIR"/output_images/Musketeer/tile_0_0.png");
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 0.5f;
    m_attackSpeed = 18;
    m_cost = 17;
    m_rangeCoordinate.push_back({0, 96});
    m_rangeCoordinate.push_back({-48, 48});
    m_rangeCoordinate.push_back({0, 48});
    m_rangeCoordinate.push_back({48, 48});
    m_rangeCoordinate.push_back({-96, 0});
    m_rangeCoordinate.push_back({-48, 0});
    m_rangeCoordinate.push_back({48, 0});
    m_rangeCoordinate.push_back({96, 0});
    m_rangeCoordinate.push_back({-48, -48});
    m_rangeCoordinate.push_back({0, -48});
    m_rangeCoordinate.push_back({48, -48});
    m_rangeCoordinate.push_back({0, -96});
    for(int _=0; _<12; _++){
        m_rangeTile.push_back(std::make_shared<Tile>(m_rangeImagePath));
    }

    // 子彈
    // image = RESOURCE_DIR"/output_images/Musketeer/bullet_0_1.png"
    bulletImage = std::make_shared<Util::Image>(RESOURCE_DIR"/output_images/Musketeer/bullet_0_1.png");
    LOG_INFO("Image loaded");

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

    // // 升級花費
    // m_upgradeCost = std::make_shared<Util::GameObject>();
    // m_upgradeCost->SetZIndex(15);
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
        attackdown.push_back(RESOURCE_DIR"/output_images/Musketeer/tile_4_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        attackup.push_back(RESOURCE_DIR"/output_images/Musketeer/tile_5_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        attackright.push_back(RESOURCE_DIR"/output_images/Musketeer/tile_6_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        attackleft.push_back(RESOURCE_DIR"/output_images/Musketeer/tile_7_" + std::to_string(i) +".png");
    }


    LOG_INFO("Musketeer built");
}

bool Musketeer::IsEnemyInRange(const std::shared_ptr<Enemy> enemy){
    int x = -(((int)enemy->m_Transform.translation.y+240+24)/48-10);
    int y = (((int)enemy->m_Transform.translation.x+480+24)/48);
    int m_x = -(((int)m_coordinate.y+240+24)/48-10);
    int m_y = (((int)m_coordinate.x+480+24)/48);
    return abs(x-m_x) + abs(y-m_y) <= 2;
}

void Musketeer::Update_for_speccial_guard(){
    // Musketeer 攻擊
    if(m_attackable && static_cast<int>(m_enemyInRange.size()) >= 1){
        
        m_attackable = false;

        
        // 創造子彈、放進vec_Bullet
        std::shared_ptr<Util::GameObject> tem_bullet = Guard::CreatBullet();
        vec_bullet.push_back(tem_bullet);
        LOG_INFO("built tem_bullet");

        // 動畫開始
        attacking = true;

        // 找動畫方向
        attack_direction = FindDirectionofFirstEnemy(m_enemyInRange[0]);
        
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
            SetImage(RESOURCE_DIR"/output_images/Musketeer/tile_0_0.png");
            // LOG_INFO("Set origin picture");
        }
    }
    // 確定有敵人
    if((int)m_enemyInRange.size() != 0){
        // ----讀敵人資料----
        std::shared_ptr<Enemy> firstenemy = m_enemyInRange[0];
        float firstenmy_x = firstenemy->GetTransform().translation.x;
        float firstenmy_y = firstenemy->GetTransform().translation.y;
        // ----------------
        for(int i=0;i<(int)vec_bullet.size();i++){
            if(int(m_enemyInRange.size()) == 0){
                vec_bullet.clear();
                break;
            }
            auto bullet = vec_bullet[i];
            // ----畫子彈------
            bullet->Draw();
            // ----------------
            
            // ----子彈移動-----
            BulletMove(bullet, firstenmy_x, firstenmy_y);
            //----------------
            float delta_x = bullet->m_Transform.translation.x - firstenmy_x;
            float delta_y = bullet->m_Transform.translation.y - firstenmy_y;
            
            // LOG_INFO(now_dx);
            // LOG_INFO(now_dy);
            if(delta_x * delta_x + delta_y * delta_y <= 150){
                vec_bullet.erase(vec_bullet.begin() + i);
                i--;
                // 為了怕同時造成傷害時，第二次傷害對nullptr造成傷害
                if((int) m_enemyInRange.size() != 0){
                    if(m_enemyInRange[0]->GetHealth() > 0){
                        m_enemyInRange[0]->GetHurt(m_damage);
                    }
                    if(m_enemyInRange[0]->IsDead()){
                        // 打死敵人就清空vec_bullet
                        vec_bullet.clear();
                        PopFrontEnemyInRange();
                    }
                }
            }
        }
    }
    // // 刪除已經碰到敵人的子彈
    // for (int i=0;i<(int)vec_bullet.size();i++) {
    //     LOG_INFO("Delete the arrive bullet");
    //     if (vec_bullet[i].second == false) {
    //         vec_bullet.erase(vec_bullet.begin() + i);
    //         i--;
    //     }
    // }
    // LOG_INFO((int)vec_bullet.size());
}

void Musketeer::Upgrade(){
    if(m_rank < m_maxrank && m_level->m_player_money_now >= 10*m_rank + (m_rank - 3)*(m_rank - 2)*(m_rank - 1)){
        m_damage += 0.5;
        m_attackSpeed *= 1.2;
        m_rank += 1;
        LOG_INFO("Musketeer upgraded");
    }
    else{
        LOG_INFO("upgrade fail");
    }
}