#ifndef DRAGON_HPP
#define DRAGON_HPP

#include <string>

#include "Guard.hpp"

class Dragon : public Guard {
public:
    Dragon();

    void Update_for_speccial_guard() override;

    bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) override;

    bool IsEnemyInHiddenRange(const std::shared_ptr<Enemy> enemy) override;

    void Upgrade() override;

private:
};

#endif