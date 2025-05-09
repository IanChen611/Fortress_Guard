#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "ReadEnemy.hpp"
#include "Level.hpp"

ReadEnemy::ReadEnemy(std::vector<std::vector<glm::vec2>> ways, Level* level){
    m_ways = ways;
    m_level = level;
    level_num = m_level->m_level;
    
    if(level_num != 999){
        std::string fileName = RESOURCE_DIR"/Enemy_Wave/Level" + std::to_string(level_num) + ".csv";
        file.open(fileName);
        if (!file.is_open()) {
            LOG_INFO("The file Enemy_Wave's Level" + std::to_string(level_num) + ".csv cannot be opened.");
            return;
        }
        if(file.is_open()){
            LOG_INFO("The file Enemy_Wave's Level" + std::to_string(level_num) + ".csv is opened.");
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
                        // 大史萊姆
                        if(cell[1] == 'K'){
                            int num = cell[2] - '0';
                            tem_enemy = std::make_shared<SlimeKing>(m_ways[num-1], m_level);
                        }
                        // 中史萊姆
                        else if(cell[1] == 'M'){
                            int num = cell[2] - '0';
                            tem_enemy = std::make_shared<MegaSlime>(m_ways[num-1], m_level);
                        }
                        // 小史萊姆
                        else{
                            int num = cell[1] - '0';
                            tem_enemy = std::make_shared<Slime>(m_ways[num-1], m_level);
                        }
                    }
                    else if(cell[0] == 'O'){
                        int num  = cell[1] - '0';
                        tem_enemy = std::make_shared<Orc>(m_ways[num-1], m_level);
                    }
                    else if(cell[0] == 'M'){
                        int num  = cell[1] - '0';
                        tem_enemy = std::make_shared<Mammoth>(m_ways[num-1], m_level);
                    }
                    else if(cell[0] == 'N'){
                        int num  = cell[1] - '0';
                        // tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Necromancer/tile_0_0.png", m_ways[num-1], 5000.0f, 0.2f);
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
}


std::vector<std::pair<std::shared_ptr<Enemy>, int>> ReadEnemy::GetEnemy(){
    if (wave >= int(EnemyList.size()) && level_num != 999) {
        // size 為 0
        std::vector<std::pair<std::shared_ptr<Enemy>, int>> a;
        return a;
    }
    wave += 1;
    if(level_num == 999){
        // CreateEndlessEnemy();
    }
    return EnemyList[wave-1];
}

//spawn enemy in endless mode 
// void ReadEnemy::CreateEndlessEnemy(){
//     healthboost *= 1.2;
//     //add more enemy in some wave
//     if(wave == 3 || wave == 5 || wave == 10){
//         enemyTypeAmount += 1;
//     }
//     std::vector<std::pair<std::shared_ptr<Enemy>, int>> WaveEnemyList;
//     srand(time(NULL));
//     int interval = 50 - wave;
//     if(interval < 10){
//         interval = 10;
//     }
//     std::shared_ptr<Enemy> tem_enemy;
    
//     //spawn boss
//     if(wave == 10){
//         tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slimeking/tile_0_0.png", m_ways[0], 2048.0f * healthboost, 0.25f);
//         WaveEnemyList.push_back(std::make_pair(tem_enemy, 50));
//     }
//     else if(wave == 20){
//         tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Necromancer/tile_0_0.png", m_ways[0], 5000.0f * healthboost, 0.2f);
//         WaveEnemyList.push_back(std::make_pair(tem_enemy, 50));
//     }
//     else if(wave % 10 == 0){
//         int temp = wave / 10;
//         for(int i=0; i<temp; i++){
//             if(i%2 == 0){
//                 tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slimeking/tile_0_0.png", m_ways[0], 2048.0f * healthboost, 0.25f);
//             }
//             else{
//                 tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Necromancer/tile_0_0.png", m_ways[0], 5000.0f * healthboost, 0.2f);
//             }
//             WaveEnemyList.push_back(std::make_pair(tem_enemy, 50));
//         }
//     }

//     //spawn normal enemy
//     for(int i=0; i<3*wave; i++){
//         if(i == 3 * wave - 1){
//             interval = 1500 - 20 * wave;
//             if(interval < 0){
//                 interval = 0;
//             }
//         }
//         int x = rand() % enemyTypeAmount;
//         if(x == 0){
//             //slime
//             tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", m_ways[0], 8.0f * healthboost, 1.0f);
//         }
//         else if(x == 1){
//             //orc
//             tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Orc/tile_0_0.png", m_ways[0], 120.0f * healthboost, 0.4f);
//         }
//         else if(x == 2){
//             //mammoth
//             tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Mammoth/tile_0_0.png", m_ways[0], 50.0f * healthboost, 2.5f);
//         }
//         else if(x == 3){
//             //megaslime
//             tem_enemy = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/MegaSlime/tile_0_0.png", m_ways[0], 128.0f * healthboost, 0.5f);
//         }
//         WaveEnemyList.push_back(std::make_pair(tem_enemy, interval));
//     }
//     EnemyList.push_back(WaveEnemyList);
// }

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
