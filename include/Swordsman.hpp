#ifndef SWORDSMAN_HPP
#define SWORDSMAN_HPP

#include <string>

#include "Guard.hpp"

class Swordsman : public Guard {
public:
    Swordsman();

    void Update() override;

    bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) override {return abs(enemy->m_Transform.translation.x - m_Transform.translation.x) <= 1 && abs(enemy->m_Transform.translation.y - m_Transform.translation.y) <= 1;}

private:
};

#endif