#ifndef READENEMY_HPP
#define READENEMY_HPP

#include "Enemy.hpp"

#include "Util/Logger.hpp"

class Enemy;

class ReadEnemy{
public:
    ReadEnemy(int level);

    std::vector<std::pair<std::shared_ptr<Enemy>, int>> GetEnemy();

    void SetWayPoint(int number, std::vector<glm::vec2>);

private:
    std::ifstream file;
    
    int wave = 0;
    std::vector<std::vector<std::pair<std::shared_ptr<Enemy>, int>>> EnemyList;

    std::vector<glm::vec2> waypoint1;
    std::vector<glm::vec2> waypoint2;
    std::vector<glm::vec2> waypoint3;
};



#endif