#ifndef READENEMY_HPP
#define READENEMY_HPP

// #include "Level.hpp" this can't be included
#include "Enemy.hpp"
#include "Slime.hpp"
#include "Orc.hpp"
#include "Mammoth.hpp"
#include "MegaSlime.hpp"
#include "SlimeKing.hpp"
#include "Necromancer.hpp"

#include "Util/Logger.hpp"

class Enemy;
class Level;

class ReadEnemy{
public:
    ReadEnemy(std::vector<std::vector<glm::vec2>> ways, Level* level);

    std::vector<std::pair<std::shared_ptr<Enemy>, int>> GetEnemy();

    // void CreateEndlessEnemy();

    // void SetWayPoint(int number, std::vector<glm::vec2> waypoint);

private:
    Level* m_level;

    int level_num;

    std::ifstream file;
    
    int wave = 0;

    std::vector<std::vector<std::pair<std::shared_ptr<Enemy>, int>>> EnemyList;

    std::vector<std::vector<glm::vec2>> m_ways;
    
    int enemyTypeAmount = 1;

    float healthboost = 1;
};



#endif