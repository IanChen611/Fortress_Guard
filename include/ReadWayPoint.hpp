#ifndef READWAYPOINT_HPP
#define READWAYPOINT_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


#include "Util/Logger.hpp"

#include "Enemy.hpp"

class ReadWayPoint{
public:
    ReadWayPoint(Level* level);

    std::vector<std::vector<glm::vec2>> GetWayPoint();


private:
    Level* m_level;

    int level_num;

    std::ifstream file;

    std::vector<std::vector<glm::vec2>> m_Waypoints;

};

#endif