#include "Guard.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

Guard::Guard(){
    // 升級按鈕
    m_upgradeButton = std::make_shared<Button>(
        RESOURCE_DIR"/Image/UI/upgrade_button.png",
        this->m_Transform.translation.x,
        this->m_Transform.translation.y,
        32, 32,
        1.0f, 1.0f,
        [this]() { 
            this->Upgrade();
        }
    );
    m_upgradeButton->SetZIndex(15);
    m_upgradeButton->SetVisible(false);

    // 升級花費
    m_upgradeCost = std::make_shared<Util::GameObject>();
    m_upgradeCost->SetZIndex(15);
    m_upgradeCost_text = std::make_shared<Util::Text>(
        RESOURCE_DIR"/Font/Inter.ttf",
        15, std::to_string(10),
        Util::Color(254, 254, 0));
    m_upgradeCost->SetDrawable(m_upgradeCost_text);
    
    //等級UI
    m_ranknumber = std::make_shared<Util::GameObject>();
    m_ranknumber->SetZIndex(15);
    m_ranknumber->SetVisible(false);
    m_ranknumber_text = std::make_shared<Util::Text>(
        RESOURCE_DIR"/Font/Inter.ttf",
        16, std::to_string(m_rank),
        Util::Color(0, 0, 0));
    m_ranknumber->SetDrawable(m_ranknumber_text);

    // 攻擊冷卻UI
    m_cooldown_bar = std::make_shared<Util::GameObject>();
    m_cooldown_bar_IMG = std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/cooldown_bar.png");
    m_cooldown_bar->SetDrawable(m_cooldown_bar_IMG);
    m_cooldown_bar->SetPivot({0, -24});
    m_cooldown_bar->SetZIndex(15);
    m_cooldown_bar->SetVisible(false);
}

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

void Guard::SetPosition(const glm::vec2& Position) {
    m_Transform.translation = Position;
    m_upgradeButton->m_Transform.translation = {Position.x, Position.y + 48};
    m_upgradeCost->m_Transform.translation = {Position.x + 7, Position.y + 20};
    m_ranknumber->m_Transform.translation = {Position.x + 7, Position.y - 25};
    m_cooldown_bar->m_Transform.translation = {Position.x + 21, Position.y - 24};
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
        bool mouse_inside = (mouse_pos.x == m_coordinate.x && mouse_pos.y == m_coordinate.y);
        if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)){
            m_clickMe_RB = true;
        }
        if(Util::Input::IsKeyUp(Util::Keycode::MOUSE_RB)){
            m_clickMe_RB = false;
        }
        // 滑鼠右鍵按下 + 範圍內
        if(mouse_inside && m_clickMe_RB){
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
            if(!m_clickMe_LB_down && Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && mouse_inside){
                m_clickMe_LB_down = true;
                // LOG_INFO("m_clickMe_LB_down = " + std::to_string(m_clickMe_LB_down));
            }
            // 剛剛滑鼠左鍵按下過 + 滑鼠左鍵鬆開 + 範圍內
            if(m_clickMe_LB_down && Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && mouse_inside){
                m_clickMe_LB_down = false;
                m_clickMe_LB = !m_clickMe_LB;
                // LOG_INFO("m_clickMe_LB = " + std::to_string(m_clickMe_LB));
                m_upgradeButton->SetVisible(m_clickMe_LB);
                m_upgradeCost->SetVisible(m_clickMe_LB);
                m_ranknumber->SetVisible(m_clickMe_LB);
            }
            // 按下但不在物件上
            bool mouse_on_upgrade_button = (mouse_pos.y == m_coordinate.y + 48 && mouse_pos.x == m_coordinate.x);
            // LOG_INFO(mouse_on_upgrade_button);
            if(m_clickMe_LB && Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && !(mouse_inside || mouse_on_upgrade_button)){
                m_clickMe_LB = false;
                m_upgradeButton->SetVisible(false);
                m_upgradeCost->SetVisible(false);
                m_ranknumber->SetVisible(false);
            }
        }
        // 判定查看該位Guard
        if(m_clickMe_LB){
            // 可以升級的時候
            if(m_rank < 3){
                m_ranknumber_text->SetText("Lv." + std::to_string(m_rank));
                // 花費
                m_upgradeCost_text->SetText(std::to_string(10*(m_rank)));
                m_upgradeCost->Draw();
                // 升級按鈕
                m_upgradeButton->Draw();
                m_upgradeButton->Update();
            }
            else{
                m_ranknumber_text->SetText("Lv.Max");
            }
            m_ranknumber->Draw();
        }
        // --------------------


        // -----攻擊冷卻相關-------
        if(cooldown_bar_scale > 0 || !m_attackable) cooldown_bar_scale = m_attackTime;
        else cooldown_bar_scale = 0;
        m_cooldown_bar->m_Transform.scale.y = cooldown_bar_scale * 0.01;
        m_cooldown_bar->SetVisible(true);
        // LOG_INFO("Drawing cooldown_bar");
        m_cooldown_bar->Draw();
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
        //detect enemy is dead or not
        if(static_cast<int>(m_enemyInRange.size()) >= 1){
            if(m_enemyInRange[0]->IsDead()){
                PopFrontEnemyInRange();
            }
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
        // --------------------
    }
}