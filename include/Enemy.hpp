#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include <string>

#include "Util/GameObject.hpp"

class Level;

// class Enemy : public Util::GameObject {
// public:
//     Enemy(const std::string& ImagePath, const std::vector<glm::vec2> waypoints, const float health, const float moveSpeed);

//     // ~Enemy() = default;

//     void Update();

//     void SetImage(const std::string& ImagePath);

//     void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

//     void SetHealth(const float health) {m_health_ori = health;m_health_now = health;}

//     void setMoveSpeed(const float moveSpeed) {m_moveSpeed = moveSpeed;}

//     void Move();

//     bool IsDead(){return m_isDead;}

//     int GiveMoney(){return enemyDropMoneyAmount;}

//     void GetHurt(float damage);

//     float GetHealth(){return m_health_now;}

//     std::string GetImagePath(){return m_ImagePath;}

//     std::vector<glm::vec2> GetWaypoints(){return m_waypoints;}

// private:
//     std::string m_ImagePath;
//     std::vector<glm::vec2> m_waypoints;
//     std::shared_ptr<Util::GameObject> m_healthbar;
//     float m_health_ori;
//     float m_health_now;
//     float m_moveSpeed;
//     bool m_isDead = false;
//     int enemyDropMoneyAmount = 3;
//     int coordinate1 = 1;
//     int coordinate2 = 1;

//     // 移動動畫
//     std::string move_direction;
//     int now_picture = 0;
//     int num_picture = 5;
//     int past_time = 0;
//     int time_gap = 0;
//     std::vector<std::string> move_right;
//     std::vector<std::string> move_left;
//     std::vector<std::string> move_up;
//     std::vector<std::string> move_down;
// };

class Enemy : public Util::GameObject {
public:
    Enemy();

    void Update();

    virtual void Update_for_speccial_enemy() = 0;

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position;}

    void SetHealth(const float health) {m_health_ori = health;m_health_now = health;}

    void setMoveSpeed(const float moveSpeed) {m_moveSpeed = moveSpeed;}

    void Move();

    bool IsDead(){return m_isDead;}

    void GetHurt(float damage);

    float GetHealth(){return m_health_now;} // wait for deleted?

    std::string GetImagePath(){return m_ImagePath;} // wait for deleted

    std::vector<glm::vec2> GetWaypoints(){return m_waypoints;} // wait for deleted

protected:
    std::string m_ImagePath;
    std::vector<glm::vec2> m_waypoints;
    std::shared_ptr<Util::GameObject> m_healthbar;
    float m_health_ori;
    float m_health_now;
    float m_moveSpeed;
    bool m_isDead = false;
    int enemyDropMoneyAmount = 3;
    int coordinate1 = 1;
    int coordinate2 = 1;

    // 移動動畫
    std::string move_direction;
    int now_picture = 0;
    int num_picture = 5;
    int past_time = 0;
    int time_gap = 0;
    std::vector<std::string> move_right;
    std::vector<std::string> move_left;
    std::vector<std::string> move_up;
    std::vector<std::string> move_down;

    // level
    Level* m_level;
};

#endif