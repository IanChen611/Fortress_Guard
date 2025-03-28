#include "Guard.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

// Guard::Guard(const std::string& myselfImagePath) {
//     SetImage(myselfImagePath);
//     m_Transform.scale = {3, 3};
//     SetZIndex(10);
//     LOG_INFO("Guard built");
// }

void Guard::SetImage(const std::string& myselfImagePath) {
    m_myselfImagePath = myselfImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_myselfImagePath);
}

void Guard::SetEnemyInRange(std::shared_ptr<Enemy> enemy){
    m_enemyInRange.push_back(enemy);
}

void Guard::PopFrontEnemyInRange(){
    m_enemyInRange.erase(m_enemyInRange.begin());
}

void Guard::Update(){
    //something special
    Update_for_speccial_guard();
    if(!m_isDeployed){
        //change myself coordinates and range coordinates
        glm::vec2 mouse_pos = Util::Input::GetCursorPosition();
        m_coordinate.x = (((int)mouse_pos.x+480+24)/48-10)*48;
        m_coordinate.y = (((int)mouse_pos.y+240+24)/48-5)*48;
        SetPosition(m_coordinate);
        // 放在路徑上 => m_canDeployed = false => 不顯示range
        if(m_canDeployed){
            for(int i=0; static_cast<std::size_t>(i) < m_rangeCoordinate.size(); i++){
                glm::vec2 tempCoordinate = {m_rangeCoordinate[i].x+m_coordinate.x, m_rangeCoordinate[i].y+m_coordinate.y};
                m_rangeTile[i]->SetZIndex(3);
                m_rangeTile[i]->SetPosition(tempCoordinate);
                m_rangeTile[i]->Draw();
            }
        }
    }
    else if(m_isDeployed){
        //show range
        glm::vec2 mouse_pos = Util::Input::GetCursorPosition();
        mouse_pos.x = (((int)mouse_pos.x+480+24)/48-10)*48;
        mouse_pos.y = (((int)mouse_pos.y+240+24)/48-5)*48;
        if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)){
            m_clickMe_RB = true;
        }
        if(Util::Input::IsKeyUp(Util::Keycode::MOUSE_RB)){
            m_clickMe_RB = false;
        }
        // 滑鼠右鍵按下 + 範圍內
        if(mouse_pos.x == m_coordinate.x && mouse_pos.y == m_coordinate.y && m_clickMe_RB){
            for(int i=0; static_cast<std::size_t>(i) < m_rangeCoordinate.size(); i++){
                m_rangeTile[i]->Draw();
            }
        }
        // -------升級按鈕-------
        // 消除放置以為升級之問題
        if(!eliminated_deployed_problem){
            eliminated_deployed_problem = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);
        }
        // 以消除放置之問題
        if(eliminated_deployed_problem){
            // 滑鼠左鍵按下 + 範圍內
            if(!m_clickMe_LB_down && Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && mouse_pos.x == m_coordinate.x && mouse_pos.y == m_coordinate.y){
                m_clickMe_LB_down = true;
                LOG_INFO("m_clickMe_LB_down = " + std::to_string(m_clickMe_LB_down));
            }
            // 剛剛滑鼠左鍵按下過 + 滑鼠左鍵鬆開 + 範圍內
            if(m_clickMe_LB_down && Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && mouse_pos.x == m_coordinate.x && mouse_pos.y == m_coordinate.y){
                m_clickMe_LB_down = false;
                m_clickMe_LB = !m_clickMe_LB;
                LOG_INFO("m_clickMe_LB = " + std::to_string(m_clickMe_LB));
                m_upgradeButton->SetVisible(m_clickMe_LB);
            }
        }
        
        if(m_clickMe_LB){
            m_upgradeButton->Draw();
            m_upgradeButton->Update();
        }
        // --------------------



        // 判斷攻擊冷卻好了沒
        if(m_attackTime <= 0 && !m_attackable){
            m_attackable = true;
            m_attackTime += 100;
            // LOG_INFO("attackable is true");
        }
        // 不能攻擊，冷卻中
        if(m_attackTime > 0 && !m_attackable){
            m_attackTime -= m_attackSpeed/2;
            // LOG_INFO(m_attackTime);
        }
        // 攻擊交給special_Update()
        // if(m_attackable && static_cast<int>(m_enemyInRange.size()) >= 1){
        //     m_enemyInRange[0]->GetHurt(m_damage);
        //     if(m_enemyInRange[0]->IsDead()){
        //         PopFrontEnemyInRange();
        //     }
        //     m_attackable = false;
        // }
        // LOG_INFO(m_enemyInRange.size());
    }
}