#ifndef SLIME_HPP
#define SLIME_HPP

#include "Enemy.hpp"
// #include "Monster.hpp"

class Slime : public Enemy {
public:
    Slime(const std::vector<glm::vec2> waypoints, Level* level);

    void Update_for_speccial_enemy() override;
    
private:
};

#endif