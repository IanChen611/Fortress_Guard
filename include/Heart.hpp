#ifndef HEART_HPP
#define HEART_HPP


#include "Util/GameObject.hpp"


class Heart : public Util::GameObject {
public:
    Heart(int pos_X, int pos_Y, int index, int* castlehealth_now);
    ~Heart() = default;

    void Update() override;
    void SetImage(const std::string& ImagePath);
private:
    std::string m_heart_full_imgpath;
    std::string m_heart_empty_imgpath;
    int m_index;
    int *m_castlehealth_now;
};
#endif