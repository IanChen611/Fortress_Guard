#include "Util/Logger.hpp"
#include "Level.hpp"
#include "SlimeKing.hpp"
#include "MegaSlime.hpp"

SlimeKing::SlimeKing(const std::vector<glm::vec2> waypoints, Level* level){
    m_waypoints = waypoints;
    m_level = level;
    m_EnemyType = "SlimeKing";
    SetImage(RESOURCE_DIR"/output_images/MegaSlime/tile_0_0.png");
    SetHealth(2048.0f);
    setMoveSpeed(0.25f);
    SetPosition({-480.0f+48*m_waypoints[0].y, 240.0f-48*m_waypoints[0].x});
    m_waypoints.erase(m_waypoints.begin());
    for(int i=0;i<=5;i++){
        move_down.push_back(RESOURCE_DIR"/output_images/Slimeking/tile_0_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_left.push_back(RESOURCE_DIR"/output_images/Slimeking/tile_1_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_right.push_back(RESOURCE_DIR"/output_images/Slimeking/tile_2_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_up.push_back(RESOURCE_DIR"/output_images/Slimeking/tile_3_" + std::to_string(i) +".png");
    }
    time_gap = 20;
    LOG_INFO("SlimeKing built");
}

void SlimeKing::Update_for_speccial_enemy() {
    // spawn 4 megaslime after died
    if(m_isDead){
        std::vector<glm::vec2> tem_waypoints = m_waypoints;
        glm::vec2 tem_position = m_Transform.translation;
        float y = ((int)tem_position.x+480+24)/48;
        float x = -(((int)tem_position.y+240+24)/48-10);
        tem_position = {x, y};
        for(int i = 0; i < 4; i++){
            //change position
            if(tem_position.x == m_waypoints[0].x){
                if(tem_position.y < m_waypoints[0].y){
                    tem_waypoints.insert(tem_waypoints.begin(), {tem_position.x, tem_position.y-0.5*i});
                }
                else if(tem_position.y > m_waypoints[0].y){
                    tem_waypoints.insert(tem_waypoints.begin(), {tem_position.x, tem_position.y+0.5*i});
                }
            }
            else if(tem_position.y == m_waypoints[0].y){
                if(tem_position.x < m_waypoints[0].x){
                    tem_waypoints.insert(tem_waypoints.begin(), {tem_position.x-0.5*i, tem_position.y});
                }
                else if(tem_position.x > m_waypoints[0].x){
                    tem_waypoints.insert(tem_waypoints.begin(), {tem_position.x+0.5*i, tem_position.y});
                }
            }
            else{
                tem_waypoints.push_back({99999,99999});
            }
            // spawn megaslime
            std::shared_ptr<Enemy> tem_enemy = std::make_shared<MegaSlime>(tem_waypoints, m_level);
            if(m_level->m_level == 999){
                tem_enemy->SetHealth(tem_enemy->GetHealth()*m_health_ori/2048);
                tem_enemy->setMoveSpeed(tem_enemy->GetMoveSpeed()*m_moveSpeed/0.25);
            }
            m_level->enemyList.push_back(tem_enemy);
        }
    }
}