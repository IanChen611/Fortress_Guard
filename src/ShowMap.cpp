#include "ShowMap.hpp"
#include "Enemy.hpp"

#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"


ShowMap::ShowMap(std::vector<glm::vec2> waypoints){
    m_waypoints = waypoints;
    SetImage(RESOURCE_DIR"/Image/UI/spot.png");
    m_Transform.scale = {0.25f, 0.25f};
    SetZIndex(100);
    setMoveSpeed(10);
    SetPosition({-480.0f+48*m_waypoints[0].y, 240.0f-48*m_waypoints[0].x});
    LOG_INFO("ShowMap built");
}

void ShowMap::SetImage(const std::string& ImagePath) {
    m_Drawable = std::make_shared<Util::Image>(ImagePath);
}

void ShowMap::Update(){
    Draw();
    if(m_waypoints[0].x != 99999 && m_waypoints[0].y != 99999){
        Move();
    }
    else{
        SetVisible(false);
        m_arrived = true;
    }
}



void ShowMap::Move(){
    if(m_Transform.translation.x == -480.0f+48*m_waypoints[0].y && m_Transform.translation.y == 240.0f-48*m_waypoints[0].x){
        m_waypoints.erase(m_waypoints.begin());
        coordinate1 = 1;
        coordinate2 = 1;
    }
    else{
        // 如果 自己的x 跟 目的地的x 一樣 => 移動y
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