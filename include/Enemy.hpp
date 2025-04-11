#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include <string>

#include "Util/GameObject.hpp"

class Enemy : public Util::GameObject {
public:
    Enemy(const std::string& ImagePath, const std::vector<glm::vec2> waypoints, const float health, const float moveSpeed);

    // ~Enemy() = default;

    void Update();

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetHealth(const float health) {m_health_ori = health;m_health_now = health;}

    void setMoveSpeed(const float moveSpeed) {m_moveSpeed = moveSpeed;}

    void Move();

    bool IsDead(){return m_isDead;}

    int GiveMoney(){return enemyDropMoneyAmount;}

    void GetHurt(float damage);

    float GetHealth(){return m_health_now;}

private:
    std::string m_ImagePath;
    std::vector<glm::vec2> m_waypoints;
    std::shared_ptr<Util::GameObject> m_healthbar;
    float m_health_ori;
    float m_health_now;
    float m_moveSpeed;
    bool m_isDead = false;
    int enemyDropMoneyAmount = 10;
};

#endif