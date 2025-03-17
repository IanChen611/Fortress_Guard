#ifndef SWORDSMAN_HPP
#define SWORDSMAN_HPP

#include <string>

#include "Guard.hpp"

class Swordsman : public Guard {
public:
    Swordsman();

    void Update() override;

    bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) override;

private:
};

#endif