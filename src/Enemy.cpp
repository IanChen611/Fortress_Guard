#include "Enemy.hpp"

#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"

Enemy::Enemy(const std::string& ImagePath, const std::vector<glm::vec2> waypoints, const float health, const float moveSpeed) {
    SetImage(ImagePath);
    SetHealth(health);
    setMoveSpeed(moveSpeed);
    m_waypoints = waypoints;
    m_Transform.scale = {3, 3};
    SetZIndex(5);
    SetPosition({-480.0f+48*m_waypoints[0].y, 240.0f-48*m_waypoints[0].x});
    m_waypoints.erase(m_waypoints.begin());
    LOG_INFO("Enemy built");

    // Enemy's health bar
    m_healthbar = std::make_shared<Util::GameObject>();
    m_healthbar->SetZIndex(11);
    m_healthbar->m_Transform.scale = {1.0f, 0.5f};
    m_healthbar->SetPivot({-24.0f, 0});
    m_healthbar->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/bar.png"));
}

void Enemy::Update(){
    m_healthbar->m_Transform.translation = {m_Transform.translation.x - 24, m_Transform.translation.y + 34};
    // m_health_now -= 1;
    // m_healthbar->m_Transform.scale = {float(m_health_now / m_health_ori), 1.0f};
    m_healthbar->Draw();
    if(m_isDead){
        SetVisible(false);
        // m_healthbar->SetVisible(false);
    }

    if(m_waypoints[0].x != 99999 && m_waypoints[0].y != 99999){
        Move();
    }
    else{
        if(!m_isDead){
            LOG_INFO("Enemy hit castle");
            m_isDead = true;
        }
    }
    if(m_health_now <= 0){
        m_isDead = true;
    }
}

void Enemy::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void Enemy::Move(){
    if(m_Transform.translation.x == -480.0f+48*m_waypoints[0].y && m_Transform.translation.y == 240.0f-48*m_waypoints[0].x){
        m_waypoints.erase(m_waypoints.begin());
        coordinate1 = 1;
        coordinate2 = 1;
    }
    else{
        if(m_Transform.translation.x == -480.0f+48*m_waypoints[0].y){
            if(m_Transform.translation.y < 240.0f-48*m_waypoints[0].x){
                m_Transform.translation.y += 1*m_moveSpeed;
                coordinate1 = -1;
            }
            else{
                m_Transform.translation.y -= 1*m_moveSpeed;
                coordinate2 = -1;
            }
            if(coordinate1 + coordinate2 != 0){
                coordinate1 = 1;
                coordinate2 = 1;
                m_Transform.translation.y = 240.0f-48*m_waypoints[0].x;
            }
        }
        else if(m_Transform.translation.y == 240.0f-48*m_waypoints[0].x){
            if(m_Transform.translation.x < -480.0f+48*m_waypoints[0].y){
                m_Transform.translation.x += 1*m_moveSpeed;
                coordinate1 = -1;
            }
            else{
                m_Transform.translation.x -= 1*m_moveSpeed;
                coordinate2 = -1;
            }
            if(coordinate1 + coordinate2 != 0){
                coordinate1 = 1;
                coordinate2 = 1;
                m_Transform.translation.x = -480.0f+48*m_waypoints[0].y;
            }
        }
    }
}

void Enemy::GetHurt(float damage){
    m_health_now -= damage;
    m_healthbar->m_Transform.scale = {float(m_health_now) / float(m_health_ori), m_healthbar->m_Transform.scale.y};
    m_healthbar->Draw();
    // LOG_INFO(m_health_now);
    // LOG_INFO(m_healthbar->m_Transform.scale);
    if(m_health_now <= 0){
        m_isDead = true;
    }
}