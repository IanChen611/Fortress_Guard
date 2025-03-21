#include "Mage.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"

Mage::Mage(){
    SetImage(RESOURCE_DIR"/output_images/Mage/tile_0_0.png");
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 8;
    m_attackSpeed = 1;
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
    LOG_INFO("Mage built");
}

bool Mage::IsEnemyInRange(const std::shared_ptr<Enemy> enemy){
    int x = -(((int)enemy->m_Transform.translation.y+240+24)/48-10);
    int y = (((int)enemy->m_Transform.translation.x+480+24)/48);
    int m_x = -(((int)m_coordinate.y+240+24)/48-10);
    int m_y = (((int)m_coordinate.x+480+24)/48);
    return abs(x-m_x) + abs(y-m_y) <= 3;
}

void Mage::Update_for_speccial_guard(){
    for(int i=0; static_cast<std::size_t>(i) < m_rangeCoordinate.size(); i++){
        glm::vec2 tempCoordinate = {m_rangeCoordinate[i].x+m_coordinate.x, m_rangeCoordinate[i].y+m_coordinate.y};
        m_rangeTile[i]->SetZIndex(3);
        m_rangeTile[i]->SetPosition(tempCoordinate);
        m_rangeTile[i]->Draw();
    }
}