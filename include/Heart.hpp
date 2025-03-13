#ifndef HEART_HPP
#define HEART_HPP


#include "Ui.hpp"


class Heart : public Ui {
public:
    Heart(int pos_X, int pos_Y, int index, int* castlehealth_now);
    ~Heart() = default;

    void Update() override;
    
private:
    std::string m_heart_full_imgpath;
    std::string m_heart_empty_imgpath;
    int m_index;
    int *m_castlehealth_now;
};
#endif