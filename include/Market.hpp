#ifndef MARKET_HPP
#define MARKET_HPP

#include "Guard.hpp"

class Market : public Guard {
    public:
        Market();
    
        void Update_for_speccial_guard() override;
    
        bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) override;
    
        void Upgrade() override;
    
    private:
    };

#endif