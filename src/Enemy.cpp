#include "Enemy.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

Enemy::Enemy(const std::string& ImagePath, const std::vector<glm::vec2> waypoints, const int health, const float moveSpeed) {
    LOG_INFO("Tile built");
    SetImage(ImagePath);
    SetHealth(health);
    setMoveSpeed(moveSpeed);
    m_waypoints = waypoints;
}

void Enemy::Update(){

}

void Enemy::Draw(){

}

void Enemy::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}