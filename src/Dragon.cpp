#include "Dragon.hpp"
#include "Enemy.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"

Dragon::Dragon(){
    SetImage(RESOURCE_DIR"/output_images/Dragon/tile_0_0.png");
    m_Transform.scale = {1.5, 1.5};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 10;
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
    // ...
    // ...
    // ...
    // ...
    // ...

    LOG_INFO("Dragon built finish");
}

bool Dragon::IsEnemyInRange(const std::shared_ptr<Enemy> enemy){
    int x = -(((int)enemy->m_Transform.translation.y+240+24)/48-10);
    int y = (((int)enemy->m_Transform.translation.x+480+24)/48);
    int m_x = -(((int)m_coordinate.y+240+24)/48-10);
    int m_y = (((int)m_coordinate.x+480+24)/48);
    return abs(x-m_x) + abs(y-m_y) <= 2;
}

void Dragon::Update_for_speccial_guard(){
    // 畫子彈
    bullet->Draw();

    // Dragon 攻擊
    if(m_attackable && static_cast<int>(m_enemyInRange.size()) >= 1){
        bullet_flying = true;
        m_attackable = false;
        bullet->SetVisible(true);
        bullet->m_Transform.translation.x = m_coordinate.x;
        bullet->m_Transform.translation.y = m_coordinate.y;
    }
    if(bullet_flying){
        if(int(m_enemyInRange.size()) == 0){
            bullet->SetVisible(false);
            return;
        }
        // ...
        // ...
        // ...
        // ...
        // ...
        if(now_dx * now_dx + now_dy * now_dy <= 150){
            bullet->SetVisible(false);
            // 為了怕同時造成傷害時，第二次傷害對nullptr造成傷害
            for(std::shared_ptr enemy : m_enemyInRange){
                if(enemy->GetHealth() > 0){
                    int x = -(((int)enemy->m_Transform.translation.y+240+24)/48-10);
                    int y = (((int)enemy->m_Transform.translation.x+480+24)/48);
                    int m_x = -(((int)m_coordinate.y+240+24)/48-10);
                    int m_y = (((int)m_coordinate.x+480+24)/48);
                    if(abs(x-m_x) + abs(y-m_y) <= 1){
                        m_enemyInRange[0]->GetHurt(m_damage);
                    }
                }
            }
            if(m_enemyInRange[0]->IsDead()){
                PopFrontEnemyInRange();
            }
            bullet_flying = false;
        }
    }
}

void Dragon::Upgrade(){
    if(m_rank < 3 && m_canUpgrade){
        m_damage += 5;
        m_attackSpeed *= 1.5;
        m_rank += 1;
        LOG_INFO("Dragon upgraded");
        m_isUpgraded = true;
    }
    else{
        LOG_INFO("upgrade fail");
    }
}