#include "Swordsman.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

Swordsman::Swordsman() {
    m_myselfImagePath = RESOURCE_DIR"/output_images/Swordsman/tile_0_0.png";
    SetImage(m_myselfImagePath);
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 10;
    m_attackSpeed = 1.5;
    m_cost = 15;
    LOG_INFO("Swordsman built");
}

void Swordsman::Update(){

}