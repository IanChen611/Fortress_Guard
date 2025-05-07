#ifndef MAMMOTH_HPP
#define MAMMOTH_HPP

#include "Enemy.hpp"
// class Enemy;
// class Level;

class Mammoth : public Enemy{
public:
    Mammoth(const std::vector<glm::vec2> waypoints, Level* level);
    void Update_for_speccial_enemy() override;
private:
};



#endif