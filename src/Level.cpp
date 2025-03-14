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


#include "Util/Logger.hpp"
#include "Util/Input.hpp"


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

    // 開始遊戲倒數
    // ---倒數的數字---
    m_countdown_number = std::make_shared<Util::GameObject>();
    m_countdown_number->SetZIndex(5);
    // m_countdown_text->m_Transform.translation = {0.0f, 0.0f};
    LOG_INFO("Test");
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
    m_SceneManager->PopScene();
}



void Level::EnemyHitCastle(){
    m_castlehealth_now -= 1;
}