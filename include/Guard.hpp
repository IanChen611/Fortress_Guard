#ifndef GUARD_HPP
#define GUARD

#include <string>

#include "Util/GameObject.hpp"

class Guard : public Util::GameObject {
public:
    Guard(const std::string& myselfImagePath);

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

protected:
    std::string m_myselfImagePath;
    std::string m_rangeImagePath;
    glm::vec2 m_coordinate;
    int m_damage;
    float m_attackSpeed;
    bool m_isDeployed = false;
    int m_cost;
    std::vector<glm::vec2> m_range;
};

#endif