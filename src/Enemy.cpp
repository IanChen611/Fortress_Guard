#include "Enemy.hpp"

#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"

#include "Level.hpp"

// Enemy::Enemy(const std::string& ImagePath, const std::vector<glm::vec2> waypoints, const float health, const float moveSpeed) {
//     SetImage(ImagePath);
//     SetHealth(health);
//     setMoveSpeed(moveSpeed);
//     m_waypoints = waypoints;
//     m_Transform.scale = {3, 3};
//     SetZIndex(5);
//     SetPosition({-480.0f+48*m_waypoints[0].y, 240.0f-48*m_waypoints[0].x});
//     m_waypoints.erase(m_waypoints.begin());
//     LOG_INFO("Enemy built");

//     // Enemy's health bar
//     m_healthbar = std::make_shared<Util::GameObject>();
//     m_healthbar->SetZIndex(11);
//     m_healthbar->m_Transform.scale = {1.0f, 0.5f};
//     m_healthbar->SetPivot({-24.0f, 0});
//     m_healthbar->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/bar.png"));

//     // 動畫預設先下
//     move_direction = "right";
//     // 讀取動畫圖
//     if(ImagePath == RESOURCE_DIR"/output_images/Slimeking/tile_0_0.png"){
//         for(int i=0;i<=5;i++){
//             move_down.push_back(RESOURCE_DIR"/output_images/Slimeking/tile_0_" + std::to_string(i) +".png");
//         }
//         for(int i=0;i<=5;i++){
//             move_left.push_back(RESOURCE_DIR"/output_images/Slimeking/tile_1_" + std::to_string(i) +".png");
//         }
//         for(int i=0;i<=5;i++){
//             move_right.push_back(RESOURCE_DIR"/output_images/Slimeking/tile_2_" + std::to_string(i) +".png");
//         }
//         for(int i=0;i<=5;i++){
//             move_up.push_back(RESOURCE_DIR"/output_images/Slimeking/tile_3_" + std::to_string(i) +".png");
//         }
//         time_gap = 20;
//     }
//     else if(ImagePath == RESOURCE_DIR"/output_images/MegaSlime/tile_0_0.png"){
//         for(int i=0;i<=5;i++){
//             move_down.push_back(RESOURCE_DIR"/output_images/MegaSlime/tile_0_" + std::to_string(i) +".png");
//         }
//         for(int i=0;i<=5;i++){
//             move_up.push_back(RESOURCE_DIR"/output_images/MegaSlime/tile_1_" + std::to_string(i) +".png");
//         }
//         for(int i=0;i<=5;i++){
//             move_right.push_back(RESOURCE_DIR"/output_images/MegaSlime/tile_2_" + std::to_string(i) +".png");
//         }
//         for(int i=0;i<=5;i++){
//             move_left.push_back(RESOURCE_DIR"/output_images/MegaSlime/tile_3_" + std::to_string(i) +".png");
//         }
//         time_gap = 15;
//     }
//     else if(ImagePath == RESOURCE_DIR"/output_images/Necromancer/tile_0_0.png"){
//         for(int i=0;i<=5;i++){
//             move_down.push_back(RESOURCE_DIR"/output_images/Necromancer/tile_0_" + std::to_string(i) +".png");
//         }
//         for(int i=0;i<=5;i++){
//             move_up.push_back(RESOURCE_DIR"/output_images/Necromancer/tile_1_" + std::to_string(i) +".png");
//         }
//         for(int i=0;i<=5;i++){
//             move_right.push_back(RESOURCE_DIR"/output_images/Necromancer/tile_2_" + std::to_string(i) +".png");
//         }
//         for(int i=0;i<=5;i++){
//             move_left.push_back(RESOURCE_DIR"/output_images/Necromancer/tile_3_" + std::to_string(i) +".png");
//         }
//         time_gap = 20;
//     }

// }

// void Enemy::Update(){
//     m_healthbar->m_Transform.translation = {m_Transform.translation.x - 24, m_Transform.translation.y + 34};
//     // m_health_now -= 1;
//     // m_healthbar->m_Transform.scale = {float(m_health_now / m_health_ori), 1.0f};
//     m_healthbar->Draw();
//     if(m_isDead){
//         SetVisible(false);
//         // m_healthbar->SetVisible(false);
//     }

    

//     if(m_waypoints[0].x != 99999 && m_waypoints[0].y != 99999){
//         Move();
//         // 動畫更新
//         past_time += 1;
//         if(past_time >= time_gap){
//             now_picture = (now_picture + 1)%num_picture;
//             past_time = 0;
//         }
//         if(move_direction == "right"){
//             SetImage(move_right[now_picture]);
//         }
//         if(move_direction == "left"){
//             SetImage(move_left[now_picture]);
//         }
//         if(move_direction == "up"){
//             SetImage(move_up[now_picture]);
//         }
//         if(move_direction == "down"){
//             SetImage(move_down[now_picture]);
//         }
        
//     }
//     else{
//         if(!m_isDead){
//             LOG_INFO("Enemy hit castle");
//             m_isDead = true;
//         }
//     }
//     if(m_health_now <= 0){
//         m_isDead = true;
//     }
// }

// void Enemy::SetImage(const std::string& ImagePath) {
//     m_ImagePath = ImagePath;

//     m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
// }

// void Enemy::Move(){
//     if(m_Transform.translation.x == -480.0f+48*m_waypoints[0].y && m_Transform.translation.y == 240.0f-48*m_waypoints[0].x){
//         m_waypoints.erase(m_waypoints.begin());
//         coordinate1 = 1;
//         coordinate2 = 1;
//     }
//     else{
//         // 如果 自己的x 跟 目的地的x 一樣 => 移動y
//         if(m_Transform.translation.x == -480.0f+48*m_waypoints[0].y){
//             if(m_Transform.translation.y < 240.0f-48*m_waypoints[0].x){
//                 m_Transform.translation.y += 1*m_moveSpeed;
//                 move_direction = "up";
//                 coordinate1 = -1;
//             }
//             else{
//                 m_Transform.translation.y -= 1*m_moveSpeed;
//                 move_direction = "down";
//                 coordinate2 = -1;
//             }
//             if(coordinate1 + coordinate2 != 0){
//                 coordinate1 = 1;
//                 coordinate2 = 1;
//                 m_Transform.translation.y = 240.0f-48*m_waypoints[0].x;
//             }
//         }
//         else if(m_Transform.translation.y == 240.0f-48*m_waypoints[0].x){
//             if(m_Transform.translation.x < -480.0f+48*m_waypoints[0].y){
//                 m_Transform.translation.x += 1*m_moveSpeed;
//                 move_direction = "right";
//                 coordinate1 = -1;
//             }
//             else{
//                 m_Transform.translation.x -= 1*m_moveSpeed;
//                 move_direction = "left";
//                 coordinate2 = -1;
//             }
//             if(coordinate1 + coordinate2 != 0){
//                 coordinate1 = 1;
//                 coordinate2 = 1;
//                 m_Transform.translation.x = -480.0f+48*m_waypoints[0].y;
//             }
//         }
//     }
// }

// void Enemy::GetHurt(float damage){
//     m_health_now -= damage;
//     if(m_health_now <= 0) m_healthbar->m_Transform.scale = {0, m_healthbar->m_Transform.scale.y};
//     else{
//         m_healthbar->m_Transform.scale = {float(m_health_now) / float(m_health_ori), m_healthbar->m_Transform.scale.y};
//     }
//     m_healthbar->Draw();
//     // LOG_INFO(m_health_now);
//     // LOG_INFO(m_healthbar->m_Transform.scale);
//     if(m_health_now <= 0){
//         m_isDead = true;
//     }
// }

Enemy::Enemy(){
    m_Transform.scale = {3, 3};
    SetZIndex(5);

    // enemy's health bar
    m_healthbar = std::make_shared<Util::GameObject>();
    m_healthbar->SetZIndex(11);
    m_healthbar->m_Transform.scale = {1.0f, 0.5f};
    m_healthbar->SetPivot({-24.0f, 0});
    m_healthbar->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/bar.png"));
    // LOG_INFO("Monster built");
}

void Enemy::Update(){
    Update_for_speccial_enemy();

    m_healthbar->m_Transform.translation = {m_Transform.translation.x - 24, m_Transform.translation.y + 34};
    m_healthbar->Draw();
    if(m_isDead){
        SetVisible(false);
        m_level->m_player_money_now += enemyDropMoneyAmount;
        LOG_INFO("get money");
    }

    // movement
    if(m_waypoints[0].x != 99999 && m_waypoints[0].y != 99999){
        Move();
        // 動畫更新
        past_time += 1;
        if(past_time >= time_gap){
            now_picture = (now_picture + 1)%num_picture;
            past_time = 0;
        }
        if(move_direction == "right"){
            SetImage(move_right[now_picture]);
        }
        if(move_direction == "left"){
            SetImage(move_left[now_picture]);
        }
        if(move_direction == "up"){
            SetImage(move_up[now_picture]);
        }
        if(move_direction == "down"){
            SetImage(move_down[now_picture]);
        }
    }
    else{
        if(!m_isDead){
            LOG_INFO("Enemy hit castle");
            m_level->m_castlehealth_now -= 1;
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
        // 如果 自己的x 跟 目的地的x 一樣 => 移動y
        if(m_Transform.translation.x == -480.0f+48*m_waypoints[0].y){
            if(m_Transform.translation.y < 240.0f-48*m_waypoints[0].x){
                m_Transform.translation.y += 1*m_moveSpeed;
                move_direction = "up";
                coordinate1 = -1;
            }
            else{
                m_Transform.translation.y -= 1*m_moveSpeed;
                move_direction = "down";
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
                move_direction = "right";
                coordinate1 = -1;
            }
            else{
                m_Transform.translation.x -= 1*m_moveSpeed;
                move_direction = "left";
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
    if(m_health_now <= 0) m_healthbar->m_Transform.scale = {0, m_healthbar->m_Transform.scale.y};
    else{
        m_healthbar->m_Transform.scale = {float(m_health_now) / float(m_health_ori), m_healthbar->m_Transform.scale.y};
    }
    m_healthbar->Draw();
    if(m_health_now <= 0){
        m_isDead = true;
    }
}