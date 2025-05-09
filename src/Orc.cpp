#include "Util/Logger.hpp"
#include "Orc.hpp"

Orc::Orc(const std::vector<glm::vec2> waypoints, Level* level){
    m_waypoints = waypoints;
    m_level = level;
    m_EnemyType = "Orc";
    SetImage(RESOURCE_DIR"/output_images/Orc/tile_0_0.png");
    SetHealth(120.0f);
    setMoveSpeed(0.4f);
    SetPosition({-480.0f+48*m_waypoints[0].y, 240.0f-48*m_waypoints[0].x});
    m_waypoints.erase(m_waypoints.begin());
    for(int i=0;i<=5;i++){
        move_down.push_back(RESOURCE_DIR"/output_images/Orc/tile_0_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_up.push_back(RESOURCE_DIR"/output_images/Orc/tile_1_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_right.push_back(RESOURCE_DIR"/output_images/Orc/tile_2_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_left.push_back(RESOURCE_DIR"/output_images/Orc/tile_3_" + std::to_string(i) +".png");
    }
    time_gap = 18;
    LOG_INFO("Orc built");
}

void Orc::Update_for_speccial_enemy() {

}