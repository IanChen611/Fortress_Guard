#ifndef SHOWMAP_HPP
#define SHOWMAP_HPP

#include "Util/GameObject.hpp"



class ShowMap : Util::GameObject{
public:
    ShowMap(std::vector<glm::vec2> waypoints);

    void Update();

    void Move();
    void setMoveSpeed(const float moveSpeed) {m_moveSpeed = moveSpeed;}

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position;}

    void SetImage(const std::string& ImagePath);

    bool IsArrived(){return m_arrived;}


protected:
    // 移動
    std::vector<glm::vec2> m_waypoints;
    float m_moveSpeed;
    int coordinate1;
    int coordinate2;

    // 抵達了沒
    bool m_arrived = false;

};




#endif