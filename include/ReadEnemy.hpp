#ifndef READENEMY_HPP
#define READENEMY_HPP

#include "Enemy.hpp"

#include "Util/Logger.hpp"

class Enemy;

class ReadEnemy{
public:
    ReadEnemy(std::vector<std::vector<glm::vec2>> ways, int level);

    std::vector<std::pair<std::shared_ptr<Enemy>, int>> GetEnemy();

    // void SetWayPoint(int number, std::vector<glm::vec2> waypoint);

private:
    std::ifstream file;
    
    int wave = 0;
    std::vector<std::vector<std::pair<std::shared_ptr<Enemy>, int>>> EnemyList;

    std::vector<std::vector<glm::vec2>> m_ways;
    
};



#endif