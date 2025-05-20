#ifndef SWORDSMAN_HPP
#define SWORDSMAN_HPP

#include <string>

#include "Guard.hpp"

class Swordsman : public Guard {
public:
    Swordsman(Level* level);

    void Update_for_speccial_guard() override;

    bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) override;

    bool IsEnemyInHiddenRange(const std::shared_ptr<Enemy> enemy) override {return false;}

    void Upgrade() override;

private:
};

#endif