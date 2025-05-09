#ifndef SLIMEKING_HPP
#define SLIMEKING_HPP

#include "Enemy.hpp"

class SlimeKing : public Enemy {
public:
    SlimeKing(const std::vector<glm::vec2> waypoints, Level* level);

    void Update_for_speccial_enemy() override;
    
private:
};

#endif