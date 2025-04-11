#include "Market.hpp"

#include "Util/Logger.hpp"

Market::Market() {
    SetImage(RESOURCE_DIR"/output_images/Market/tile_2_2.png");
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_damage = 10;
    m_attackSpeed = 0.5;
    m_cost = 30;
    LOG_INFO("Market built");
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