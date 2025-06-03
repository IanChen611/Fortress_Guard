#include "Dragon.hpp"
#include "Level.hpp"

#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"

Dragon::Dragon(Level* level){
    m_level = level;
    SetImage(RESOURCE_DIR"/output_images/Dragon/tile_0_0.png");
    m_Transform.scale = {1.5, 1.5};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 7;
    m_attackSpeed = 0.8;
    m_cost = 23;
    m_isRange = true;
    m_attackRange = 1;
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
    // image = RESOURCE_DIR"/output_images/Dragon/fireball_0_0.png"
    bulletImage = std::make_shared<Util::Image>(RESOURCE_DIR"/output_images/Dragon/fireball_0_0.png");
    LOG_INFO("Image loaded");
    


    // 龍的動畫預設先下
    attack_direction = "down";
    // 讀取動畫圖
    for(int i=0;i<=3;i++){
        attackdown.push_back(RESOURCE_DIR"/output_images/Dragon/tile_0_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        attackup.push_back(RESOURCE_DIR"/output_images/Dragon/tile_1_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        attackleft.push_back(RESOURCE_DIR"/output_images/Dragon/tile_2_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        attackright.push_back(RESOURCE_DIR"/output_images/Dragon/tile_3_" + std::to_string(i) +".png");
    }

    LOG_INFO("Dragon built finish");
}

bool Dragon::IsEnemyInRange(const std::shared_ptr<Enemy> enemy){
    int x = -(((int)enemy->m_Transform.translation.y+240+24)/48-10);
    int y = (((int)enemy->m_Transform.translation.x+480+24)/48);
    int m_x = -(((int)m_coordinate.y+240+24)/48-10);
    int m_y = (((int)m_coordinate.x+480+24)/48);
    return abs(x-m_x) + abs(y-m_y) <= 2;
}

bool Dragon::IsEnemyInHiddenRange(const std::shared_ptr<Enemy> enemy){
    int x = -(((int)enemy->m_Transform.translation.y+240+24)/48-10);
    int y = (((int)enemy->m_Transform.translation.x+480+24)/48);
    int m_x = -(((int)m_coordinate.y+240+24)/48-10);
    int m_y = (((int)m_coordinate.x+480+24)/48);
    return abs(x-m_x) + abs(y-m_y) <= 3;
}

void Dragon::Update_for_speccial_guard(){
    
    if((int)(m_enemyInRange.size()) >= 1) attack_direction = FindDirectionofFirstEnemy(m_enemyInRange[0]);
    // 動畫 => 面向第一個敵人
    picture_interval += 1*m_level->gameSpeed;
    if(picture_interval >= 10){
        now_picture = (now_picture + 1) % 4;
        if(attack_direction == "down"){
            SetImage(attackdown[now_picture]);
        }
        else if(attack_direction == "up"){
            SetImage(attackup[now_picture]);
        }
        else if(attack_direction == "left"){
            SetImage(attackleft[now_picture]);
        }
        else if(attack_direction == "right"){
            SetImage(attackright[now_picture]);
        }
        picture_interval = 0;
    }

    // Dragon 攻擊(創造子彈)
    if(m_attackable && static_cast<int>(m_enemyInRange.size()) >= 1){
        m_attackable = false;

        // 創造子彈、放進vec_Bullet
        std::shared_ptr<Util::GameObject> tem_bullet = Guard::CreatBullet();
        vec_bullet.push_back(tem_bullet);
        LOG_INFO("built tem_bullet");
    }
    if((int)m_enemyInRange.size() != 0){
        // ----讀敵人資料----
        std::shared_ptr<Enemy> firstenemy = m_enemyInRange[0];
        float firstenmy_x = firstenemy->GetTransform().translation.x;
        float firstenmy_y = firstenemy->GetTransform().translation.y;
        // ----------------
        for(int i=0;i<(int)vec_bullet.size();i++){
            if(int(m_enemyInRange.size()) == 0){
                vec_bullet.clear();
                return;
            }
            auto bullet = vec_bullet[i];
            // ----畫子彈---
            bullet->Draw();
            // -------------
             // ----子彈移動-----
            BulletMove(bullet, firstenmy_x, firstenmy_y);

            //----檢測距離-----
            float delta_x = bullet->m_Transform.translation.x - firstenmy_x;
            float delta_y = bullet->m_Transform.translation.y - firstenmy_y;
            if(delta_x * delta_x + delta_y * delta_y <= 150){
                LOG_INFO("Dragon bullet hit enemy.");
                vec_bullet.erase(vec_bullet.begin() + i);
                i--;
                // 為了怕同時造成傷害時，第二次傷害對nullptr造成傷害
                // for 迴圈遍歷 m_enemyInRange
                // enemy is the iterator
                for(auto enemy : m_enemyInHiddenRange){
                    if(enemy->GetHealth() > 0){
                        int x = -(((int)enemy->m_Transform.translation.y+240+24)/48-10);
                        int y = (((int)enemy->m_Transform.translation.x+480+24)/48);
                        int m_x = -(((int)m_enemyInRange[0]->m_Transform.translation.y+240+24)/48-10);
                        int m_y = (((int)m_enemyInRange[0]->m_Transform.translation.x+480+24)/48);
                        if(abs(x-m_x) + abs(y-m_y) <= 1 && enemy != nullptr && enemy->GetHealth() > 0){
                            enemy->GetHurt(m_damage);
                        }
                    }
                }
                if(m_enemyInRange[0]->IsDead()){
                    PopFrontEnemyInRange();
                    // 打死敵人就清空vec_bullet
                    vec_bullet.clear();
                    return;
                }
                if(m_enemyInHiddenRange[0]->IsDead()){
                    PopFrontEnemyInHiddenRange();
                }
            }
        }
    }
    // -------------------------
    
}

void Dragon::Upgrade(){
    if(m_rank < m_maxrank && m_level->m_player_money_now >= 10*m_rank + (m_rank - 3)*(m_rank - 2)*(m_rank - 1)){
        m_damage += 5;
        m_attackSpeed *= 1.5;
        m_rank += 1;
        m_level->m_player_money_now -= 10*m_rank + (m_rank - 3)*(m_rank - 2)*(m_rank - 1);
        LOG_INFO("Dragon upgraded");
    }
    else{
        LOG_INFO("upgrade fail");
    }
}