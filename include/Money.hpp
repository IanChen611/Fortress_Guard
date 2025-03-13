#ifndef MONEY_HPP
#define MONEY_HPP

#include <string>

#include "Ui.hpp"

#include "Util/Text.hpp"

class Money : public Ui{
public:
    Money(int pos_X, int pos_Y, int* player_money);    
    ~Money() = default;
    
    void Update() override;
private:
    std::string m_money_imgpath;
    int m_index;
    int *m_player_money;

    // std::shared_ptr<Util>
};

#endif
