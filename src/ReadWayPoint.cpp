#include "ReadWayPoint.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Level.hpp"



ReadWayPoint::ReadWayPoint(Level* level){
    m_level = level;
    level_num = m_level->m_level;
    // 讀檔
    std::string fileName = RESOURCE_DIR"/WayPoints/Level" + std::to_string(level_num) + ".csv";
    file.open(fileName);
    if (!file.is_open()) {
        LOG_INFO("The file WayPoints's Level" + std::to_string(level_num) + ".csv cannot be opened.");
        return;
    }
    if(file.is_open()){
        LOG_INFO("The file WayPoints's Level" + std::to_string(level_num) + ".csv is opened.");
    }
    // 
    std::string line;
    LOG_INFO("ReadWayPoint way:");
    while(getline(file, line)){
        std::stringstream lineStream(line);
        std::string cell;
        glm::vec2 tem_waypoint;
        std::vector<glm::vec2> vec_waypoint;
        while(getline(lineStream, cell, ',')){
            tem_waypoint.x = std::stoi(cell);
            getline(lineStream, cell, ',');
            tem_waypoint.y = std::stoi(cell);
            LOG_INFO(std::to_string(tem_waypoint.x) + ", " + std::to_string(tem_waypoint.y));
            vec_waypoint.push_back(tem_waypoint);
        }
        m_Waypoints.push_back(vec_waypoint);
        vec_waypoint.clear();
    }
}


std::vector<std::vector<glm::vec2>> ReadWayPoint::GetWayPoint(){
    return m_Waypoints;
}