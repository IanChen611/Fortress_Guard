#ifndef MEGASLIME_HPP
#define MEGASLIME_HPP

#include "Enemy.hpp"

class MegaSlime : public Enemy {
public:
    MegaSlime(const std::vector<glm::vec2> waypoints, Level* level);

    void Update_for_speccial_enemy() override;
    
private:
};

#endif