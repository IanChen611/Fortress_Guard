#ifndef MUSKETEER_HPP
#define MUSKETEER_HPP

#include <string>

#include "Guard.hpp"

class Musketeer : public Guard {
public:
    Musketeer();

    void Update_for_speccial_guard() override;

    bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) override;

private:
};

#endif