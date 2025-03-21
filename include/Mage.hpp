#ifndef Mage_HPP
#define Mage_HPP

#include <string>

#include "Guard.hpp"

class Mage : public Guard {
    public:
        Mage();
    
        void Update_for_speccial_guard() override;
    
        bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) override;
    
    private:
    };

#endif