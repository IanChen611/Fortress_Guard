#include "Util/Logger.hpp"
#include "Mammoth.hpp"

Mammoth::Mammoth(const std::vector<glm::vec2> waypoints, Level* level){
    m_waypoints = waypoints;
    m_level = level;
    SetImage(RESOURCE_DIR"/output_images/Mammoth/tile_0_0.png");
    SetHealth(50.0f);
    setMoveSpeed(2.5f);
    SetPosition({-480.0f+48*m_waypoints[0].y, 240.0f-48*m_waypoints[0].x});
    m_waypoints.erase(m_waypoints.begin());
    for(int i=0;i<=3;i++){
        move_right.push_back(RESOURCE_DIR"/output_images/Mammoth/tile_0_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        move_left.push_back(RESOURCE_DIR"/output_images/Mammoth/tile_1_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        move_down.push_back(RESOURCE_DIR"/output_images/Mammoth/tile_2_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=3;i++){
        move_up.push_back(RESOURCE_DIR"/output_images/Mammoth/tile_3_" + std::to_string(i) +".png");
    }
    time_gap = 5;
    num_picture = 3;
    LOG_INFO("Mammoth built");
}

void Mammoth::Update_for_speccial_enemy() {

}