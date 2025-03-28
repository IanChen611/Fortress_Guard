#ifndef SWORDSMAN_HPP
#define SWORDSMAN_HPP

#include <string>

#include "Guard.hpp"

class Swordsman : public Guard {
public:
    Swordsman();

    void Update_for_speccial_guard() override;

    bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) override;

    void Upgrade() override;

private:
};

#endif