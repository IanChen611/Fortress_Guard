#include "Level.hpp"

#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"
#include "Button.hpp"
#include "Enemy.hpp"
#include "Heart.hpp"
#include "Ui.hpp"
#include "Money.hpp"
#include "Guard.hpp"
#include "Swordsman.hpp"
#include "Mage.hpp"

#include "ReadMap.hpp"


#include "Util/Logger.hpp"
#include "Util/Input.hpp"

class Swordsman;

class Mage;

Level::Level(){
    // -----UI------ 

    // 返回前頁之按鈕
    UI.push_back(std::make_shared<Button>(RESOURCE_DIR"/Image/UI/back.png",
    -437, 298, 170, 116, 0.5f, 0.5f,
    [this]() { 
        this->OnClickBackPreScene();
    }));

    // -----血量顯示-----
    m_castlehealth_now = m_castlehealth_ori;
    for(int i=0;i<m_castlehealth_ori;i++){
        UI.push_back(std::make_shared<Heart>(448 - i * 64, 300, i+1, &m_castlehealth_now));
    }
    // -----------


    // -----錢幣-----
    m_player_money_now = m_player_money_ori;
    std::shared_ptr<Money> m_money = std::make_shared<Money>(-100, 300, &m_player_money_now);
    UI.push_back(m_money);
    //----------------

    // -----選角色的按鈕------
    // 取消購買的按鈕
    bt_cancelBuy = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/cancelbuy.png",
        301, -290, 238, 87, 0.75f, 0.75f,
        [this]() { 
            this->OnClickCancelBuy();
        });
    bt_cancelBuy->SetVisible(false);
    
    // Swordman的按鈕
    UI.push_back(std::make_shared<Button>(RESOURCE_DIR"/output_images/Swordsman/tile_0_0.png",
        -432, -288, 16, 16, 3.0f, 3.0f,
        [this]() { 
            this->OnClickBuyGuard("Swordsman");
        }));
    // Swordsman的錢幣顯示
    std::shared_ptr<Ui> number_money_Swordsman = std::make_shared<Ui>();
    number_money_Swordsman->m_Transform.translation = {-425, -240};
    std::shared_ptr<Util::Text> number_money_text_swordsman = std::make_shared<Util::Text>(
        RESOURCE_DIR"/Font/Inter.ttf",
        30, std::to_string(15),
        Util::Color(254, 254, 0));
    number_money_Swordsman->SetDrawable(number_money_text_swordsman);
    UI.push_back(number_money_Swordsman);

    // Mage的按鈕
    UI.push_back(std::make_shared<Button>(RESOURCE_DIR"/output_images/Mage/tile_0_0.png",
        -364, -288, 16, 16, 3.0f, 3.0f,
        [this]() { 
            this->OnClickBuyGuard("Mage");
        }));
    // Mage的錢幣顯示
    std::shared_ptr<Ui> number_money_Mage = std::make_shared<Ui>();
    number_money_Mage->m_Transform.translation = {-357, -240};
    std::shared_ptr<Util::Text> number_money_text_Mage = std::make_shared<Util::Text>(
        RESOURCE_DIR"/Font/Inter.ttf",
        30, std::to_string(20),
        Util::Color(254, 254, 0));
        number_money_Mage->SetDrawable(number_money_text_Mage);
    UI.push_back(number_money_Mage);
    // Musketeer的按鈕
    UI.push_back(std::make_shared<Button>(RESOURCE_DIR"/output_images/Musketeer/tile_0_0.png",
        -296, -288, 16, 16, 3.0f, 3.0f,
        [this]() { 
            this->OnClickBuyGuard("Musketeer");
        }));
    // Musketeer的錢幣顯示
    std::shared_ptr<Ui> number_money_Musketeer = std::make_shared<Ui>();
    number_money_Musketeer->m_Transform.translation = {-289, -240};
    std::shared_ptr<Util::Text> number_money_text_Musketeer = std::make_shared<Util::Text>(
        RESOURCE_DIR"/Font/Inter.ttf",
        30, std::to_string(17),
        Util::Color(254, 254, 0));
        number_money_Musketeer->SetDrawable(number_money_text_Musketeer);
    UI.push_back(number_money_Musketeer);

    



    // 開始遊戲倒數
    // ---倒數的數字---
    m_countdown_number = std::make_shared<Util::GameObject>();
    m_countdown_number->SetZIndex(5);
    // m_countdown_text->m_Transform.translation = {0.0f, 0.0f};
    // LOG_INFO("Test");
    m_countdown_text = std::make_shared<Util::Text>(
        RESOURCE_DIR"/Font/Inter.ttf",
        200, std::to_string(5),
        Util::Color(127, 127, 127));
    m_countdown_number->SetDrawable(m_countdown_text);
    // Update()那邊負責倒數
}

void Level::SetSceneManager(SceneManager *m_SceneManager){
    this->m_SceneManager = m_SceneManager;
}

void Level::OnClickBackPreScene(){
    LOG_INFO("Called Level::OnClickBackPreScene()");
    if(!pop_scene_next_frame){
        pop_scene_next_frame = true;
        LOG_INFO("pop_scene_next_frame changes true");
    }
    // m_SceneManager->PopScene();
}



void Level::EnemyHitCastle(){
    m_castlehealth_now -= 1;
}

void Level::OnClickBuyGuard(std::string characterName){
    buying = true;
    cancelBuy = false;
    bt_cancelBuy->SetVisible(true);
    if(characterName == "Swordsman"){
        tem = std::make_shared<Swordsman>();
    }
    if(characterName == "Mage"){
        tem = std::make_shared<Mage>();
    }
    if(characterName == "Musketeer"){
        tem = std::make_shared<Musketeer>();
    }

}

void Level::OnClickCancelBuy(){
    cancelBuy = true;
    buying = false;
}

void Level::Update(){

    if(pop_scene_next_frame){
        LOG_INFO("pop_scene_next_frame changes false");
        pop_scene_next_frame = false;
        LOG_INFO("Call SceneManager::PopScene()");
        
        m_SceneManager->PopScene();
    }
    else if(!pop_scene_next_frame){
        // 遊戲開始的倒數
        if(startGameCounter < 300 && !gameStart){
            startGameCounter += 1;
            m_countdown_text->SetText(std::to_string(5 - startGameCounter/60));
            m_countdown_number->Draw();
        }
        else if(!gameStart){
            gameStart = true;
            m_countdown_number->SetVisible(false);
            LOG_INFO("Finish Countdown");
        }
        // ------

        // 地圖更新
        m_groundset->Update();
        m_pathset->Update();

        // UI更新
        for(auto ui : UI)
        {
            ui->Update();
        }

        // 遊戲沒有輸(城堡扣完血) 且 遊戲沒有贏(敵人出動全部且沒有存在場上)
        if(!gameLose && !gameWin && !pop_scene_next_frame){
            
            // call 自己special Update
            Update_for_speccial_Level();

            // 購買Guard的部分 更新
            if(buying){
                bt_cancelBuy->Update(); // 取消按鈕
                glm::vec2 mouse_pos = Util::Input::GetCursorPosition();
                int m_ground_i = -(((int)mouse_pos.y+240+24)/48-10);
                int m_ground_j = (((int)mouse_pos.x+480+24)/48);
                if(0 <= m_ground_i && m_ground_i < 10 && 0 <= m_ground_j && m_ground_j < 20){
                    
                    // 判斷現在可不可以放上去，不行的話要告訴Guard中的canDeployed
                    if(m_ground[m_ground_i][m_ground_j]->IsTouchable()){
                        tem->SetCanDeployed(true);
                    }
                    if(!m_ground[m_ground_i][m_ground_j]->IsTouchable()){
                        tem->SetCanDeployed(false);
                    }

                    if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && m_ground[m_ground_i][m_ground_j]->IsTouchable()){
                        if(m_player_money_now-tem->GetCost() >= 0){
                            m_ground[m_ground_i][m_ground_j]->SetTouchable(false);
                            m_player_money_now -= tem->GetCost();
                            buying = false;
                            tem->SetDeployed(true);
                            GuardList.push_back(tem);
                            tem = nullptr;
                        }
                    }
                }
            }
            if(tem != nullptr){
                if(cancelBuy){
                    tem->~Guard();
                    LOG_INFO("delete tem.");
                    cancelBuy = false;
                    buying = false;
                    tem = nullptr;
                }
                else tem->Update();
            }

            //Guard 更新
            for(auto guard : GuardList){
                for(auto enemy : enemyList){
                    if(guard->IsEnemyInRange(enemy) && guard->IsEnemyInEnemyInRange(enemy)){
                        guard->SetEnemyInRange(enemy);
                    }
                    else if(!guard->IsEnemyInRange(enemy) && !guard->IsEnemyInEnemyInRange(enemy)){
                        guard->PopFrontEnemyInRange();
                    }
                }
                if(m_player_money_now - 10*(guard->GetRank()) >= 0){
                    guard->SetCanUpgrade(true);
                }
                else{
                    guard->SetCanUpgrade(false);
                }
                if(guard->IsUpgraded()){
                    guard->SetIsUpgraded(false);
                    m_player_money_now -= 10*(guard->GetRank() - 1);
                }
                guard->Update();
            }

            // 倒數結束後
            if(gameStart){
                if(int(enemyPerWave.size()) == 0){
                    enemyPerWave = m_readenemy->GetEnemy();
                }
                if(intervalCounter <= 0 && int(enemyPerWave.size()) != 0){
                    intervalCounter = enemyPerWave[0].second;
                    enemyCounter += 1;
                    enemyList.push_back(enemyPerWave[0].first);
                    enemyPerWave.erase(enemyPerWave.begin());
                }
                else if(intervalCounter > 0){
                    intervalCounter -= 1;
                }
                //enemy update
                for(int i=0; i<enemyCounter; i++){
                    enemyList[i]->Update();
                    enemyList[i]->Draw();
                    //enemy died
                    if(enemyList[i]->IsDead()){
                        if(enemyList[i]->GetHealth() > 0){
                            EnemyHitCastle();
                            if(!gameLose && !gameWin && m_castlehealth_now == 0) gameLose = true;
                        }
                        m_player_money_now += enemyList[i]->GiveMoney();
                        enemyList.erase(enemyList.begin()+i);
                        i -= 1;
                        enemyCounter -= 1;
                    }
                }
                // 判斷是不是全部敵人都是dead
                bool allDead = true;
                for(auto enemy : enemyList){
                    allDead = enemy->IsDead();
                }
                if(allDead && int(enemyPerWave.size()) == 0){
                    gameWin = true;
                }
            }
        }

        if(gameLose){
            img_gameFinish = std::make_shared<Util::GameObject>();
            img_gameFinish->SetZIndex(15);
            img_gameFinish->m_Transform.scale = {1.5f, 1.5f};
            img_gameFinish->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/GameLose.png"));
        }
        if(gameWin){
            img_gameFinish = std::make_shared<Util::GameObject>();
            img_gameFinish->SetZIndex(15);
            img_gameFinish->m_Transform.scale = {1.5f, 1.5f};
            img_gameFinish->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/GameWin.png"));
        }
    }

    
}

void Level::Draw(){

    // call 自己special Draw
    Draw_for_speccial_Level();

    // 繪製地圖、路徑
    m_groundset->Draw();
    m_pathset->Draw();

    // UI繪製
    for(auto ui:UI)
    {
        ui->Draw();
    }

    
    // 購買Guard的部分 繪製
    if(buying) bt_cancelBuy->Draw();
    if(tem != nullptr) tem->Draw();

    //Guard 繪製
    for(auto guard : GuardList){
        guard->Draw();
    }

    // 遊戲結束(贏、輸)的圖片
    if(img_gameFinish != nullptr){
        img_gameFinish->Draw();
    }
}