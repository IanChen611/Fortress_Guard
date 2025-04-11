#include "Market.hpp"

#include "Util/Logger.hpp"

Market::Market() {
    SetImage(RESOURCE_DIR"/output_images/Market/tile_2_2.png");
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_rangeImagePath = "";
    m_damage = 10;
    m_attackSpeed = 0.5;
    m_cost = 30;
    LOG_INFO("Market built");
}

bool Market::IsEnemyInRange(const std::shared_ptr<Enemy> enemy){}

void Market::Update_for_speccial_guard(){
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

void Market::Upgrade(){
    if(m_rank < 3 && m_canUpgrade){
        m_damage += 5;
        m_attackSpeed *= 1.2;
        m_rank += 1;
        LOG_INFO("Market upgraded");
        m_isUpgraded = true;
    }
    else{
        LOG_INFO("upgrade fail");
    }
}