#include "Enemy.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

Enemy::Enemy(const std::string& ImagePath, const std::vector<glm::vec2> waypoints, const int health, const float moveSpeed) {
    LOG_INFO("Tile built");
    SetImage(ImagePath);
    SetHealth(health);
    setMoveSpeed(moveSpeed);
    m_waypoints = waypoints;
    m_Transform.scale = {3, 3};
    SetZIndex(5);
    LOG_INFO("Enemy built");
    SetPosition({-480.0f+48*m_waypoints[0].x, 240.0f-48*m_waypoints[0].y});
    m_waypoints.erase(m_waypoints.begin());
}

void Enemy::Update(){
    Move();
}

void Enemy::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void Enemy::Move(){
    if(m_Transform.translation.x == -480.0f+48*m_waypoints[0].y && m_Transform.translation.y == 240.0f-48*m_waypoints[0].x){
        m_waypoints.erase(m_waypoints.begin());
        LOG_INFO(m_waypoints[0]);
    }
    else{
        if(m_Transform.translation.x == -480.0f+48*m_waypoints[0].y){
            if(m_Transform.translation.y < 240.0f-48*m_waypoints[0].x){
                m_Transform.translation.y += 5*m_moveSpeed;
            }
            else{
                m_Transform.translation.y -= 5*m_moveSpeed;
            }
        }
        else{
            if(m_Transform.translation.x < -480.0f+48*m_waypoints[0].y){
                m_Transform.translation.x += 5*m_moveSpeed;
            }
            else{
                m_Transform.translation.x -= 5*m_moveSpeed;
            }
             
        }
    }
}