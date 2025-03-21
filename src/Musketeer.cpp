#include "Musketeer.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"

Musketeer::Musketeer(){
    SetImage(RESOURCE_DIR"/output_images/Musketeer/tile_0_0.png");
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 6;
    m_attackSpeed = 2;
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

}