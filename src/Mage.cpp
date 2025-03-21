#include "Mage.hpp"
#include "Enemy.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"

Mage::Mage(){
    SetImage(RESOURCE_DIR"/output_images/Mage/tile_0_0.png");
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 8;
    m_attackSpeed = 1.5;
    m_cost = 20;
    m_rangeCoordinate.push_back({0, 144});
    m_rangeCoordinate.push_back({-48, 96});
    m_rangeCoordinate.push_back({0, 96});
    m_rangeCoordinate.push_back({48, 96});
    m_rangeCoordinate.push_back({-96, 48});
    m_rangeCoordinate.push_back({-48, 48});
    m_rangeCoordinate.push_back({0, 48});
    m_rangeCoordinate.push_back({48, 48});
    m_rangeCoordinate.push_back({96, 48});
    m_rangeCoordinate.push_back({-144, 0});
    m_rangeCoordinate.push_back({-96, 0});
    m_rangeCoordinate.push_back({-48, 0});
    m_rangeCoordinate.push_back({48, 0});
    m_rangeCoordinate.push_back({96, 0});
    m_rangeCoordinate.push_back({144, 0});
    m_rangeCoordinate.push_back({-96, -48});
    m_rangeCoordinate.push_back({-48, -48});
    m_rangeCoordinate.push_back({0, -48});
    m_rangeCoordinate.push_back({48, -48});
    m_rangeCoordinate.push_back({96, -48});
    m_rangeCoordinate.push_back({-48, -96});
    m_rangeCoordinate.push_back({0, -96});
    m_rangeCoordinate.push_back({48, -96});
    m_rangeCoordinate.push_back({0, -144});
    for(int _=0; _<24; _++){
        m_rangeTile.push_back(std::make_shared<Tile>(m_rangeImagePath));
    }

    // 子彈
    // image = RESOURCE_DIR"/output_images/Mage/fireball_0_3.png"
    std::shared_ptr<Util::Image> bulletImage = std::make_shared<Util::Image>(RESOURCE_DIR"/output_images/Mage/fireball_0_3.png");
    LOG_INFO("Image loaded");
    bullet = std::make_shared<Util::GameObject>(); 
    bullet->SetDrawable(bulletImage);
    bullet->SetZIndex(5);
    bullet->m_Transform.scale = {1.5f, 1.5f};
    bullet->SetVisible(false);

    LOG_INFO("Mage built finish");
}

bool Mage::IsEnemyInRange(const std::shared_ptr<Enemy> enemy){
    int x = -(((int)enemy->m_Transform.translation.y+240+24)/48-10);
    int y = (((int)enemy->m_Transform.translation.x+480+24)/48);
    int m_x = -(((int)m_coordinate.y+240+24)/48-10);
    int m_y = (((int)m_coordinate.x+480+24)/48);
    return abs(x-m_x) + abs(y-m_y) <= 3;
}

void Mage::Update_for_speccial_guard(){
    // 畫子彈
    bullet->Draw();

    // Mage 攻擊
    if(m_attackable && static_cast<int>(m_enemyInRange.size()) >= 1){
        bullet_flying = true;
        m_attackable = false;
        bullet->SetVisible(true);
        bullet->m_Transform.translation.x = m_coordinate.x;
        bullet->m_Transform.translation.y = m_coordinate.y;
    }
    if(bullet_flying){
        
        std::shared_ptr<Enemy> firstenemy = m_enemyInRange[0];
        float firstenmy_x = firstenemy->GetTransform().translation.x;
        float firstenmy_y = firstenemy->GetTransform().translation.y;
        float bullet_x = bullet->GetTransform().translation.x;
        float bullet_y = bullet->GetTransform().translation.y;
        LOG_INFO("bullet_x = " + std::to_string(bullet_x));
        LOG_INFO("bullet_y = " + std::to_string(bullet_y));
        float delta_x = firstenmy_x - bullet_x;
        float delta_y = firstenmy_y - bullet_y;
        float bullet_velocity = 10;
        bullet->m_Transform.translation.x += (bullet_velocity * delta_x) / sqrt(delta_x * delta_x + delta_y * delta_y);
        bullet->m_Transform.translation.y += (bullet_velocity * delta_y) / sqrt(delta_x * delta_x + delta_y * delta_y);
        float now_dx = bullet->m_Transform.translation.x - firstenmy_x;
        float now_dy = bullet->m_Transform.translation.y - firstenmy_y;
        
        LOG_INFO(now_dx);
        LOG_INFO(now_dy);
        if(now_dx * now_dx + now_dy * now_dy <= 150){
            bullet->SetVisible(false);
            m_enemyInRange[0]->GetHurt(m_damage);
            if(m_enemyInRange[0]->IsDead()){
                PopFrontEnemyInRange();
            }
            bullet_flying = false;
        }
        
    }
}