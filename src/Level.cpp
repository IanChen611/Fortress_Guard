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
#include "Market.hpp"

#include "ReadMap.hpp"


#include "Util/Logger.hpp"
#include "Util/Input.hpp"

class Swordsman;

class Mage;

class Musketeer;

class Market;


Level::Level(int level){
    m_level = level;

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

    // -----波數顯示------
    std::shared_ptr<Ui> enemy_wave_ui = std::make_shared<Ui>();
    enemy_wave_ui->m_Transform.translation = {-250, 298};
    m_current_enemy_wave_text = std::make_shared<Util::Text>(
        RESOURCE_DIR"/Font/Inter.ttf",
        35, "Wave : " + std::to_string(current_enemy_wave),
        Util::Color(254, 0, 0));
    enemy_wave_ui->SetDrawable(m_current_enemy_wave_text);
    UI.push_back(enemy_wave_ui);
    // -------------------




    // -------------------選角色的按鈕-----------------
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

    // Market的按鈕
    UI.push_back(std::make_shared<Button>(RESOURCE_DIR"/output_images/Market/tile_2_2.png",
        -228, -288, 16, 16, 3.0f, 3.0f,
        [this]() { 
            this->OnClickBuyGuard("Market");
        }));
    // Market的錢幣顯示
    std::shared_ptr<Ui> number_money_Market = std::make_shared<Ui>();
    number_money_Market->m_Transform.translation = {-221, -240};
    std::shared_ptr<Util::Text> number_money_text_Market = std::make_shared<Util::Text>(
        RESOURCE_DIR"/Font/Inter.ttf",
        30, std::to_string(30),
        Util::Color(254, 254, 0));
    number_money_Market->SetDrawable(number_money_text_Market);
    UI.push_back(number_money_Market);

    // ----------------------------------------------------------------------------------
    
    // -----------地圖載入------------
    // --取草地--
    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            m_ground[i][j] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_0.png");
            m_ground[i][j]->SetTouchable(true);
        }
    }
    m_groundset = std::make_shared<TileSet>(m_ground);
    m_groundset->SetAllZIndex(0);
    // --取道路--
    ReadMap readmap(m_level);
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            std::string tem = readmap.GiveTileName(i, j);
            if(tem.length() != 0){
                if(tem == RESOURCE_DIR"/output_images/Tiles/tile_14_5.png"){
                    m_ground[i][j]->SetImage(tem);
                    continue;
                }
                m_path[i][j] = std::make_shared<Tile>(tem);
                m_ground[i][j]->SetTouchable(false);
            }
        }
    }
    
    m_pathset = std::make_shared<TileSet>(m_path);
    m_pathset->SetAllZIndex(1);
    LOG_INFO("Level" + std::to_string(m_level) + " built");
    // -----------地圖載入結束----------------

    // ----------怪物路線---------------
    if(m_level == 1){
        waypoints.push_back({2, 2});
        waypoints.push_back({2, 7});
        waypoints.push_back({7, 7});
        waypoints.push_back({7, 13});
        waypoints.push_back({4, 13});
        waypoints.push_back({4, 17});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 2){
        waypoints.push_back({6, 2});
        waypoints.push_back({6, 11});
        waypoints.push_back({4, 11});
        waypoints.push_back({4, 17});
        waypoints.push_back({1, 17});
        waypoints.push_back({1, 11});
        waypoints.push_back({3, 11});
        waypoints.push_back({3, 2});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 3){
        // 一號路線
        waypoints.push_back({2, 1});
        waypoints.push_back({2, 7});
        waypoints.push_back({4, 7});
        waypoints.push_back({4, 17});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        // 二號路線
        waypoints.push_back({7, 11});
        waypoints.push_back({7, 7});
        waypoints.push_back({4, 7});
        waypoints.push_back({4, 17});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 4){
        // 一號路線
        waypoints.push_back({3, 0});
        waypoints.push_back({3, 13});
        waypoints.push_back({1, 13});
        waypoints.push_back({1, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        // 二號路線
        waypoints.push_back({7, 17});
        waypoints.push_back({7, 9});
        waypoints.push_back({3, 9});
        waypoints.push_back({3, 13});
        waypoints.push_back({1, 13});
        waypoints.push_back({1, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 5){
        waypoints.push_back({2, 0});
        waypoints.push_back({2, 6});
        waypoints.push_back({8, 6});
        waypoints.push_back({8, 8});
        waypoints.push_back({5, 8});
        waypoints.push_back({5, 13});
        waypoints.push_back({1, 13});
        waypoints.push_back({1, 17});
        waypoints.push_back({8, 17});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({8, 0});
        waypoints.push_back({8, 8});
        waypoints.push_back({5, 8});
        waypoints.push_back({5, 13});
        waypoints.push_back({1, 13});
        waypoints.push_back({1, 17});
        waypoints.push_back({8, 17});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({8, 9});
        waypoints.push_back({8, 13});
        waypoints.push_back({1, 13});
        waypoints.push_back({1, 17});
        waypoints.push_back({8, 17});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 6){
        waypoints.push_back({0, 1});
        waypoints.push_back({0, 5});
        waypoints.push_back({2, 5});
        waypoints.push_back({2, 7});
        waypoints.push_back({5, 7});
        waypoints.push_back({5, 4});
        waypoints.push_back({2, 4});
        waypoints.push_back({2, 7});
        waypoints.push_back({5, 7});
        waypoints.push_back({5, 12});
        waypoints.push_back({1, 12});
        waypoints.push_back({1, 17});
        waypoints.push_back({9, 17});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({8, 1});
        waypoints.push_back({8, 4});
        waypoints.push_back({5, 4});
        waypoints.push_back({5, 17});
        waypoints.push_back({9, 17});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        
        waypoints.push_back({8, 8});
        waypoints.push_back({8, 12});
        waypoints.push_back({1, 12});
        waypoints.push_back({1, 17});
        waypoints.push_back({9, 17});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 7){
        waypoints.push_back({2, 1});
        waypoints.push_back({2, 3});
        waypoints.push_back({1, 3});
        waypoints.push_back({1, 14});
        waypoints.push_back({5, 14});
        waypoints.push_back({5, 18});
        waypoints.push_back({0, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        
        waypoints.push_back({2, 1});
        waypoints.push_back({2, 3});
        waypoints.push_back({1, 3});
        waypoints.push_back({1, 9});
        waypoints.push_back({5, 9});
        waypoints.push_back({5, 3});
        waypoints.push_back({8, 3});
        waypoints.push_back({8, 14});
        waypoints.push_back({5, 14});
        waypoints.push_back({5, 10});
        waypoints.push_back({8, 10});
        waypoints.push_back({8, 14});
        waypoints.push_back({5, 14});
        waypoints.push_back({5, 18});
        waypoints.push_back({0, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({8, 0});
        waypoints.push_back({8, 3});
        waypoints.push_back({5, 3});
        waypoints.push_back({5, 9});
        waypoints.push_back({1, 9});
        waypoints.push_back({1, 14});
        waypoints.push_back({8, 14});
        waypoints.push_back({8, 10});
        waypoints.push_back({5, 10});
        waypoints.push_back({5, 18});
        waypoints.push_back({0, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 8){
        waypoints.push_back({9, 2});
        waypoints.push_back({4, 2});
        waypoints.push_back({4, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({0, 9});
        waypoints.push_back({4, 9});
        waypoints.push_back({4, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({8, 9});
        waypoints.push_back({4, 9});
        waypoints.push_back({4, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({8, 12});
        waypoints.push_back({4, 12});
        waypoints.push_back({4, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 9){
        waypoints.push_back({1, 1});
        waypoints.push_back({3, 1});
        waypoints.push_back({3, 6});
        waypoints.push_back({1, 6});
        waypoints.push_back({1, 14});
        waypoints.push_back({8, 14});
        waypoints.push_back({8, 10});
        waypoints.push_back({4, 10});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({8, 3});
        waypoints.push_back({5, 3});
        waypoints.push_back({5, 6});
        waypoints.push_back({1, 6});
        waypoints.push_back({1, 14});
        waypoints.push_back({8, 14});
        waypoints.push_back({8, 10});
        waypoints.push_back({4, 10});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({5, 17});
        waypoints.push_back({1, 17});
        waypoints.push_back({1, 14});
        waypoints.push_back({8, 14});
        waypoints.push_back({8, 10});
        waypoints.push_back({4, 10});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({5, 17});
        waypoints.push_back({8, 17});
        waypoints.push_back({8, 6});
        waypoints.push_back({1, 6});
        waypoints.push_back({1, 14});
        waypoints.push_back({8, 14});
        waypoints.push_back({8, 10});
        waypoints.push_back({4, 10});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 10){
        waypoints.push_back({4, 0});
        waypoints.push_back({4, 2});
        waypoints.push_back({0, 2});
        waypoints.push_back({0, 9});
        waypoints.push_back({7, 9});
        waypoints.push_back({7, 19});
        waypoints.push_back({5, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({4, 0});
        waypoints.push_back({4, 2});
        waypoints.push_back({9, 2});
        waypoints.push_back({9, 9});
        waypoints.push_back({2, 9});
        waypoints.push_back({2, 19});
        waypoints.push_back({5, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({4, 0});
        waypoints.push_back({4, 2});
        waypoints.push_back({0, 2});
        waypoints.push_back({0, 9});
        waypoints.push_back({9, 9});
        waypoints.push_back({9, 2});
        waypoints.push_back({0, 2});
        waypoints.push_back({0, 9});
        waypoints.push_back({2, 9});
        waypoints.push_back({2, 19});
        waypoints.push_back({5, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({4, 0});
        waypoints.push_back({4, 2});
        waypoints.push_back({9, 2});
        waypoints.push_back({9, 9});
        waypoints.push_back({0, 9});
        waypoints.push_back({0, 2});
        waypoints.push_back({9, 2});
        waypoints.push_back({9, 9});
        waypoints.push_back({7, 9});
        waypoints.push_back({7, 19});
        waypoints.push_back({5, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        waypoints.push_back({4, 0});
        waypoints.push_back({4, 2});
        waypoints.push_back({0, 2});
        waypoints.push_back({0, 9});
        waypoints.push_back({9, 9});
        waypoints.push_back({9, 2});
        waypoints.push_back({0, 2});
        waypoints.push_back({0, 9});
        waypoints.push_back({9, 9});
        waypoints.push_back({9, 2});
        waypoints.push_back({0, 2});
        waypoints.push_back({0, 9});
        waypoints.push_back({2, 9});
        waypoints.push_back({2, 19});
        waypoints.push_back({5, 19});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 11){
        // 右側出發的那個 繞最大圈
        waypoints.push_back({6, 18});
        waypoints.push_back({1, 18});
        waypoints.push_back({1, 3});
        waypoints.push_back({8, 3});
        waypoints.push_back({8, 16});
        waypoints.push_back({3, 16});
        waypoints.push_back({3, 5});
        waypoints.push_back({6, 5});
        waypoints.push_back({6, 14});
        waypoints.push_back({4, 14});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 左上出發的怪物
        waypoints.push_back({1, 0});
        waypoints.push_back({1, 3});
        waypoints.push_back({8, 3});
        waypoints.push_back({8, 16});
        waypoints.push_back({3, 16});
        waypoints.push_back({3, 5});
        waypoints.push_back({6, 5});
        waypoints.push_back({6, 14});
        waypoints.push_back({4, 14});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 左下出發的怪物
        waypoints.push_back({8, 0});
        waypoints.push_back({8, 3});
        waypoints.push_back({8, 16});
        waypoints.push_back({3, 16});
        waypoints.push_back({3, 5});
        waypoints.push_back({6, 5});
        waypoints.push_back({6, 14});
        waypoints.push_back({4, 14});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 12){
        // 左上出發 繞下半圓
        waypoints.push_back({0, 1});
        waypoints.push_back({4, 1});
        waypoints.push_back({4, 4});
        waypoints.push_back({1, 4});
        waypoints.push_back({1, 7});
        waypoints.push_back({6, 7});
        waypoints.push_back({6, 11});
        waypoints.push_back({9, 11});
        waypoints.push_back({9, 16});
        waypoints.push_back({3, 16});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 左下出發 繞下半圓
        waypoints.push_back({8, 1});
        waypoints.push_back({4, 1});
        waypoints.push_back({4, 4});
        waypoints.push_back({1, 4});
        waypoints.push_back({1, 7});
        waypoints.push_back({6, 7});
        waypoints.push_back({6, 11});
        waypoints.push_back({9, 11});
        waypoints.push_back({9, 16});
        waypoints.push_back({3, 16});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 左上出發 繞上半圓
        waypoints.push_back({0, 1});
        waypoints.push_back({4, 1});
        waypoints.push_back({4, 4});
        waypoints.push_back({1, 4});
        waypoints.push_back({1, 7});
        waypoints.push_back({6, 7});
        waypoints.push_back({6, 11});
        waypoints.push_back({1, 11});
        waypoints.push_back({1, 16});
        waypoints.push_back({3, 16});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 左下出發 繞上半圓
        waypoints.push_back({8, 1});
        waypoints.push_back({4, 1});
        waypoints.push_back({4, 4});
        waypoints.push_back({1, 4});
        waypoints.push_back({1, 7});
        waypoints.push_back({6, 7});
        waypoints.push_back({6, 11});
        waypoints.push_back({1, 11});
        waypoints.push_back({1, 16});
        waypoints.push_back({3, 16});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 右上出發 繞一圈
        waypoints.push_back({1, 19});
        waypoints.push_back({1, 11});
        waypoints.push_back({9, 11});
        waypoints.push_back({9, 16});
        waypoints.push_back({3, 16});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 右上出發 繞兩圈
        waypoints.push_back({1, 19});
        waypoints.push_back({1, 11});
        waypoints.push_back({9, 11});
        waypoints.push_back({9, 16});
        waypoints.push_back({1, 16});
        waypoints.push_back({1, 11});
        waypoints.push_back({9, 11});
        waypoints.push_back({9, 16});
        waypoints.push_back({3, 16});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 13){
        // 左上出發 繞上半部分
        waypoints.push_back({0, 0});
        waypoints.push_back({4, 0});
        waypoints.push_back({4, 5});
        waypoints.push_back({1, 5});
        waypoints.push_back({1, 11});
        waypoints.push_back({5, 11});
        waypoints.push_back({5, 13});
        waypoints.push_back({1, 13});
        waypoints.push_back({1, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        // 左上出發 繞下半部分
        waypoints.push_back({0, 0});
        waypoints.push_back({5, 0});
        waypoints.push_back({5, 5});
        waypoints.push_back({8, 5});
        waypoints.push_back({8, 7});
        waypoints.push_back({3, 7});
        waypoints.push_back({3, 9});
        waypoints.push_back({7, 9});
        waypoints.push_back({7, 15});
        waypoints.push_back({3, 15});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        // 左上出發 先繞上半 再繞下半部分
        waypoints.push_back({0, 0});
        waypoints.push_back({4, 0});
        waypoints.push_back({4, 5});
        waypoints.push_back({1, 5});
        waypoints.push_back({1, 11});
        waypoints.push_back({3, 11});
        waypoints.push_back({3, 9});
        waypoints.push_back({7, 9});
        waypoints.push_back({7, 15});
        waypoints.push_back({3, 15});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        // 左上出發 先繞下半 再繞上半部分
        waypoints.push_back({0, 0});
        waypoints.push_back({5, 0});
        waypoints.push_back({5, 5});
        waypoints.push_back({8, 5});
        waypoints.push_back({8, 7});
        waypoints.push_back({3, 7});
        waypoints.push_back({3, 11});
        waypoints.push_back({5, 11});
        waypoints.push_back({5, 13});
        waypoints.push_back({1, 13});
        waypoints.push_back({1, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 左下出發 繞上半部分
        waypoints.push_back({9, 0});
        waypoints.push_back({4, 0});
        waypoints.push_back({4, 5});
        waypoints.push_back({1, 5});
        waypoints.push_back({1, 11});
        waypoints.push_back({5, 11});
        waypoints.push_back({5, 13});
        waypoints.push_back({1, 13});
        waypoints.push_back({1, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        // 左下出發 繞下半部分  
        waypoints.push_back({9, 0});
        waypoints.push_back({5, 0});
        waypoints.push_back({5, 5});
        waypoints.push_back({8, 5});
        waypoints.push_back({8, 7});
        waypoints.push_back({3, 7});
        waypoints.push_back({3, 9});
        waypoints.push_back({7, 9});
        waypoints.push_back({7, 15});
        waypoints.push_back({3, 15});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 左下出發 先繞上半 再繞下半部分
        waypoints.push_back({9, 0});
        waypoints.push_back({4, 0});
        waypoints.push_back({4, 5});
        waypoints.push_back({1, 5});
        waypoints.push_back({1, 11});
        waypoints.push_back({3, 11});
        waypoints.push_back({3, 9});
        waypoints.push_back({7, 9});
        waypoints.push_back({7, 15});
        waypoints.push_back({3, 15});
        waypoints.push_back({3, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        // 左下出發 先繞下半 再繞上半部分
        waypoints.push_back({9, 0});
        waypoints.push_back({5, 0});
        waypoints.push_back({5, 5});
        waypoints.push_back({8, 5});
        waypoints.push_back({8, 7});
        waypoints.push_back({3, 7});
        waypoints.push_back({3, 11});
        waypoints.push_back({5, 11});
        waypoints.push_back({5, 13});
        waypoints.push_back({1, 13});
        waypoints.push_back({1, 18});
        waypoints.push_back({8, 18});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

    }
    else if(m_level == 14){
        // 左邊出發 繞下半圈
        waypoints.push_back({4, 0});
        waypoints.push_back({4, 3});
        waypoints.push_back({8, 3});
        waypoints.push_back({8, 16});
        waypoints.push_back({1, 16});
        waypoints.push_back({1, 9});
        waypoints.push_back({3, 9});
        waypoints.push_back({3, 7});
        waypoints.push_back({5, 7});
        waypoints.push_back({5, 10});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        // 左邊出發 繞一圈後繞上半圈
        waypoints.push_back({4, 0});
        waypoints.push_back({4, 3});
        waypoints.push_back({1, 3});
        waypoints.push_back({1, 16});
        waypoints.push_back({8, 16});
        waypoints.push_back({8, 3});
        waypoints.push_back({1, 3});
        waypoints.push_back({1, 9});
        waypoints.push_back({3, 9});
        waypoints.push_back({3, 7});
        waypoints.push_back({5, 7});
        waypoints.push_back({5, 10});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();

        // 右邊出發 繞下半圈
        waypoints.push_back({4, 19});
        waypoints.push_back({4, 16});
        waypoints.push_back({8, 16});
        waypoints.push_back({8, 3});
        waypoints.push_back({1, 3});
        waypoints.push_back({1, 10});
        waypoints.push_back({3, 12});
        waypoints.push_back({5, 12});
        waypoints.push_back({5, 10});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
        // 右邊出發 繞一圈後繞上半圈
        waypoints.push_back({4, 19});
        waypoints.push_back({4, 16});
        waypoints.push_back({1, 16});
        waypoints.push_back({1, 3});
        waypoints.push_back({8, 3});
        waypoints.push_back({8, 16});
        waypoints.push_back({1, 16});
        waypoints.push_back({1, 10});
        waypoints.push_back({3, 10});
        waypoints.push_back({3, 12});
        waypoints.push_back({5, 12});
        waypoints.push_back({5, 10});
        waypoints.push_back({99999, 99999});
        ways.push_back(waypoints);
        waypoints.clear();
    }
    else if(m_level == 15){}
    // 放入路線
    m_readenemy = std::make_shared<ReadEnemy>(ways, m_level);
    // ----------怪物路線設置結束-----------


    // 開始遊戲倒數
    // ---倒數的數字---
    m_countdown_number = std::make_shared<Util::GameObject>();
    m_countdown_number->SetZIndex(5);
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
    if(characterName == "Market"){
        tem = std::make_shared<Market>();
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
            // Update_for_speccial_Level();

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
                if(guard->IsAttacker()){
                    for(auto enemy : enemyList){
                        if(guard->IsEnemyInRange(enemy) && !guard->IsEnemyInEnemyInRange(enemy)){
                            guard->SetEnemyInRange(enemy);
                        }
                        else if(!guard->IsEnemyInRange(enemy) && guard->IsEnemyInEnemyInRange(enemy)){
                            guard->PopFrontEnemyInRange();
                        }
                    }
                }
                else{
                    if(guard->IsAttackable()){
                        m_player_money_now += guard->GetDamage();
                        guard->SetAttackable(false);
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
                if(int(enemyPerWave.size()) == 0){ // 目前這波敵人出完時
                    enemyPerWave = m_readenemy->GetEnemy(); //
                    ready_to_next_wave = true;
                }
                if(intervalCounter <= 0 && int(enemyPerWave.size()) != 0){
                    intervalCounter = enemyPerWave[0].second;
                    enemyCounter += 1;
                    enemyList.push_back(enemyPerWave[0].first);
                    enemyPerWave.erase(enemyPerWave.begin());
                    if(ready_to_next_wave){
                        ready_to_next_wave = false;
                        // 敵人波數加一
                        current_enemy_wave += 1; 
                        // 更新波數之text
                        m_current_enemy_wave_text->SetText("Wave : " + std::to_string(current_enemy_wave));
                    }
                }
                else if(intervalCounter > 0){
                    intervalCounter -= 1;
                }
                //enemy update
                for(int i=0; i<enemyCounter; i++){
                    //enemy died
                    enemyList[i]->Update();
                    enemyList[i]->Draw();
                    if(enemyList[i]->IsDead()){
                        std::vector<glm::vec2> tem_waypoints = enemyList[i]->GetWaypoints();
                        std::vector<glm::vec2> insert_waypoints = tem_waypoints;
                        std::string tem_imagepath = enemyList[i]->GetImagePath();
                        glm::vec2 tem_position = enemyList[i]->m_Transform.translation;
                        float y = ((int)tem_position.x+480+24)/48;
                        float x = -(((int)tem_position.y+240+24)/48-10);
                        tem_position = {x, y};
                        //slimeking or megaslime
                        if(enemyList[i]->GetImagePath() == RESOURCE_DIR"/output_images/Slimeking/tile_0_0.png" || enemyList[i]->GetImagePath() == RESOURCE_DIR"/output_images/MegaSlime/tile_0_0.png"){
                            //分裂3隻(原本就有1隻)
                            for(int j = 0; j < 4; j++){
                                //change position
                                if(tem_position.x == tem_waypoints[0].x){
                                    if(tem_position.y < tem_waypoints[0].y){
                                        insert_waypoints.insert(insert_waypoints.begin(), {tem_position.x, tem_position.y-0.5*j});
                                    }
                                    else if(tem_position.y > tem_waypoints[0].y){
                                        insert_waypoints.insert(insert_waypoints.begin(), {tem_position.x, tem_position.y+0.5*j});
                                    }
                                }
                                else if(tem_position.y == tem_waypoints[0].y){
                                    if(tem_position.x < tem_waypoints[0].x){
                                        insert_waypoints.insert(insert_waypoints.begin(), {tem_position.x-0.5*j, tem_position.y});
                                    }
                                    else if(tem_position.x > tem_waypoints[0].x){
                                        insert_waypoints.insert(insert_waypoints.begin(), {tem_position.x+0.5*j, tem_position.y});
                                    }
                                }
                                else{
                                    insert_waypoints.push_back({99999,99999});
                                }
                                // LOG_INFO(insert_waypoints[0]);
                                //build enemy
                                if(tem_imagepath == RESOURCE_DIR"/output_images/Slimeking/tile_0_0.png"){
                                    enemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/MegaSlime/tile_0_0.png", insert_waypoints, 128.0f, 0.5f));
                                }
                                else if(tem_imagepath == RESOURCE_DIR"/output_images/MegaSlime/tile_0_0.png"){
                                    enemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", insert_waypoints, 8.0f, 1.0f));
                                }
                            }
                            enemyCounter += 4;
                        }
                        //normal enemy
                        if(enemyList[i]->GetHealth() > 0){
                            EnemyHitCastle();
                            if(!gameLose && !gameWin && m_castlehealth_now == 0) gameLose = true;
                        }
                        m_player_money_now += enemyList[i]->GiveMoney();
                        LOG_INFO("get money");
                        enemyList.erase(enemyList.begin()+i);
                        i -= 1;
                        enemyCounter -= 1;
                    }
                }
                // 判斷是不是全部敵人都是dead
                // bool allDead = true;
                // for(auto enemy : enemyList){
                //     allDead = enemy->IsDead();
                // }
                if(int(enemyList.size()) == 0 && int(enemyPerWave.size()) == 0 && m_castlehealth_now > 0){
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
    // Draw_for_speccial_Level();

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