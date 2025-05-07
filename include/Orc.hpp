#ifndef ORC_HPP
#define ORC_HPP

#include "Enemy.hpp"
// class Enemy;
// class Level;

class Orc : public Enemy{
public:
    Orc(const std::vector<glm::vec2> waypoints, Level* level);
    void Update_for_speccial_enemy() override;
private:
};



#endif