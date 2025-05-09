#include "Util/Logger.hpp"
#include "Slime.hpp"

Slime::Slime(const std::vector<glm::vec2> waypoints, Level* level){
    m_waypoints = waypoints;
    m_level = level;
    m_EnemyType = "Slime";
    SetImage(RESOURCE_DIR"/output_images/Slime/tile_0_0.png");
    SetHealth(8.0f);
    setMoveSpeed(1.0f);
    SetPosition({-480.0f+48*m_waypoints[0].y, 240.0f-48*m_waypoints[0].x});
    m_waypoints.erase(m_waypoints.begin());
    for(int i=0;i<=5;i++){
        move_down.push_back(RESOURCE_DIR"/output_images/Slime/tile_0_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_left.push_back(RESOURCE_DIR"/output_images/Slime/tile_1_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_right.push_back(RESOURCE_DIR"/output_images/Slime/tile_2_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_up.push_back(RESOURCE_DIR"/output_images/Slime/tile_3_" + std::to_string(i) +".png");
    }
    time_gap = 10;
    LOG_INFO("Slime built");
}

void Slime::Update_for_speccial_enemy() {

}