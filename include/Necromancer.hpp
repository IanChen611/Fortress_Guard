#ifndef NECROMANCER_HPP
#define NECROMANCER_HPP

#include "Enemy.hpp"

class Necromancer : public Enemy {
public:
    Necromancer(const std::vector<glm::vec2> waypoints, Level* level);

    void Update_for_speccial_enemy() override;
    
private:
    int timerForSpawnEnemy = 0;
};

#endif