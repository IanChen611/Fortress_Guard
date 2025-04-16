#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "ReadEnemy.hpp"

ReadEnemy::ReadEnemy(std::vector<std::vector<glm::vec2>> ways, int level){
    m_ways = ways;
    
    std::string fileName = RESOURCE_DIR"/Enemy_Wave/Level" + std::to_string(level) + ".csv";
    file.open(fileName);
    if (!file.is_open()) {
        LOG_INFO("The file Enemy_Wave's Level" + std::to_string(level) + ".csv cannot be opened.");
        return;
    }
    if(file.is_open()){
        LOG_INFO("The file Enemy_Wave's Level" + std::to_string(level) + ".csv is opened.");
    }

    std::string line;
    int frame;
    std::shared_ptr<Enemy> tem_enemy;
    std::vector<std::pair<std::shared_ptr<Enemy>, int>> enemy_list;

    while(getline(file, line)){
        std::stringstream lineStream(line);
        std::string cell;
        bool Now_is_detect_Enemy = true;
        while(getline(lineStream, cell, ',')){
            // 現在偵測是敵人資料
            if(Now_is_detect_Enemy){
                // 史萊姆
                if(cell[0] == 'S'){
                    if(cell[1] == 'K'){
                        int num = cell[2] - '0';
                        tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slimeking/tile_0_0.png", m_ways[num-1], 128.0f, 0.25f);
                    }
                    else if(cell[1] == 'M'){
                        int num = cell[2] - '0';
                        tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/MegaSlime/tile_0_0.png", m_ways[num-1], 32.0f, 0.5f);
                    }
                    else{
                        int num = cell[1] - '0';
                        tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", m_ways[num-1], 8.0f, 1.0f);
                    }
                }
                else if(cell[0] == 'O'){
                    int num  = cell[1] - '0';
                    tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Orc/tile_0_0.png", m_ways[num-1], 50.0f, 0.5f);
                }
                else if(cell[0] == 'M'){
                    int num  = cell[1] - '0';
                    tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Mammoth/tile_0_0.png", m_ways[num-1], 30.0f, 2.0f);
                }
                else{
                    LOG_INFO("Enemy type error");
                }
            }
            else if(!Now_is_detect_Enemy){
                frame = std::stoi(cell);
                enemy_list.push_back(std::make_pair(tem_enemy, frame));
            }
            Now_is_detect_Enemy = !Now_is_detect_Enemy;
        }
        EnemyList.push_back(enemy_list);
        enemy_list.clear();
    }
}


std::vector<std::pair<std::shared_ptr<Enemy>, int>> ReadEnemy::GetEnemy(){
    if (wave >= int(EnemyList.size())) {
        // size 為 0
        std::vector<std::pair<std::shared_ptr<Enemy>, int>> a;
        return a;
    }
    wave += 1;
    return EnemyList[wave-1];
}

// void ReadEnemy::SetWayPoint(int number, std::vector<glm::vec2> waypoints){
//     if(number == 1){
//         waypoint1 = waypoints;
//     }
//     else if(number == 2){
//         waypoint2 = waypoints;
//     }
//     else if(number == 3){
//         waypoint3 = waypoints;
//     }
// }
