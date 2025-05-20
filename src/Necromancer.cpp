#include "Util/Logger.hpp"
#include "Level.hpp"
#include "Necromancer.hpp"
#include "MegaSlime.hpp"

Necromancer::Necromancer(const std::vector<glm::vec2> waypoints, Level* level){
    m_waypoints = waypoints;
    m_level = level;
    m_EnemyType = "SlimeKing";
    SetImage(RESOURCE_DIR"/output_images/Necromancer/tile_0_0.png");
    SetHealth(5000.0f);
    setMoveSpeed(0.2f);
    SetPosition({-480.0f+48*m_waypoints[0].y, 240.0f-48*m_waypoints[0].x});
    m_waypoints.erase(m_waypoints.begin());
    for(int i=0;i<=5;i++){
        move_down.push_back(RESOURCE_DIR"/output_images/Necromancer/tile_0_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_up.push_back(RESOURCE_DIR"/output_images/Necromancer/tile_1_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_right.push_back(RESOURCE_DIR"/output_images/Necromancer/tile_2_" + std::to_string(i) +".png");
    }
    for(int i=0;i<=5;i++){
        move_left.push_back(RESOURCE_DIR"/output_images/Necromancer/tile_3_" + std::to_string(i) +".png");
    }
    time_gap = 20;
    LOG_INFO("Necromancer built");
}

void Necromancer::Update_for_speccial_enemy() {
    timerForSpawnEnemy += 1*m_level->gameSpeed;
    if(timerForSpawnEnemy / 1000 > 0){
        timerForSpawnEnemy = 0;
        std::vector<glm::vec2> tem_waypoints = m_waypoints;
        glm::vec2 tem_position = m_Transform.translation;
        float y = ((int)tem_position.x+480+24)/48;
        float x = -(((int)tem_position.y+240+24)/48-10);
        tem_position = {x, y};
        tem_waypoints.insert(tem_waypoints.begin(), {tem_position.x, tem_position.y});
        std::shared_ptr<Enemy> tem_enemy = std::make_shared<MegaSlime>(tem_waypoints, m_level);
        if(m_level->m_level == 999){
            tem_enemy->SetHealth(tem_enemy->GetHealth()*m_health_ori/5000);
            tem_enemy->setMoveSpeed(tem_enemy->GetMoveSpeed()*m_moveSpeed/0.2);
        }
        m_level->enemyList.push_back(tem_enemy);
    }
}