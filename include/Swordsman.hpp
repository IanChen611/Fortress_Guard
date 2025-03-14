#ifndef SWORDSMAN_HPP
#define SWORDSMAN_HPP

#include <string>

#include "Guard.hpp"

class Swordsman : public Guard {
public:
    Swordsman(const std::string& myselfImagePath);

    void Update();

private:
    std::string m_rangeImagePath;
    glm::vec2 m_coordinate;
    int m_damage;
    float m_attackSpeed;
    bool m_isDeployed = false;
    int m_cost;
    std::vector<glm::vec2> m_range;
};

#endif