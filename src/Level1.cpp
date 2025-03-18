#include "pch.hpp"

#include "Level.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"



Level1::Level1() {
    
    // ----取圖-----
    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            m_ground1[i][j] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_0.png");
            m_ground1[i][j]->SetTouchable(true);
        }
    }
    m_groundset1 = std::make_shared<TileSet>(m_ground1);
    m_groundset1->SetAllZIndex(0);

    m_path1[2][2] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_26_6.png");
    m_path1[2][3] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_4.png");
    m_path1[2][4] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[2][5] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[2][6] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[2][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_6.png");
    m_path1[3][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path1[4][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path1[5][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path1[6][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path1[7][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_2_4.png");
    m_path1[7][8] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[7][9] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[7][10] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[7][11] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[7][12] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[7][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_2_6.png");
    m_path1[6][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path1[5][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path1[4][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_4.png");
    m_path1[4][14] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[4][15] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path1[4][16] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_6.png");
    m_path1[4][17] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_26_14.png");
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            if(m_path1[i][j] != nullptr){
                m_ground1[i][j]->SetTouchable(false);
            }
        }
    }
    m_pathset1 = std::make_shared<TileSet>(m_path1);
    m_pathset1->SetAllZIndex(1);
    LOG_INFO("Level1 built");
    // ----圖載入結束-----
    
    //----道路-----
    waypoints.push_back({2, 2});
    waypoints.push_back({2, 7});
    waypoints.push_back({7, 7});
    waypoints.push_back({7, 13});
    waypoints.push_back({4, 13});
    waypoints.push_back({4, 17});
    waypoints.push_back({99999, 99999});
    //-----swordsman test-----
    // sm = std::make_shared<Swordsman>();
    //----生成敵人---放入道路----
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
}

Level1::~Level1() {
    LOG_INFO("Level1 destroyed");
}


// void Level1::Start() {
//     LOG_INFO("Scene1 Start");
// }

void Level1::Update()  {
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
    // LOG_INFO("Level1 Updated");

    // 地圖更新
    m_groundset1->Update();
    m_pathset1->Update();

    // UI更新
    for(auto ui : UI)
    {
        ui->Update();
    }

    // 購買Guard的部分 更新
    if(buying){
        bt_cancelBuy->Update(); // 取消按鈕
        glm::vec2 mouse_pos = Util::Input::GetCursorPosition();
        int m_ground1_i = -(((int)mouse_pos.y+240+24)/48-10);
        int m_ground1_j = (((int)mouse_pos.x+480+24)/48);
        if(0 <= m_ground1_i && m_ground1_i < 10 && 0 <= m_ground1_j && m_ground1_j < 20){
            if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && m_ground1[m_ground1_i][m_ground1_j]->IsTouchable()){
                if(m_player_money_now-tem->GetCost() >= 0){
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
        for(auto enemy : EnemyList){
            if(guard->IsEnemyInRange(enemy) && guard->IsEnemyInEnemyInRange(enemy)){
                guard->SetEnemyInRange(enemy);
            }
            else if(!guard->IsEnemyInRange(enemy) && !guard->IsEnemyInEnemyInRange(enemy)){
                guard->PopFrontEnemyInRange();
            }
        }
        guard->Update();
    }

    // 倒數結束後
    if(gameStart){
        enemyTimeCounter += 1;
        int index = enemyTimeCounter/spawnTime;
        if(static_cast<std::size_t>(index) >= EnemyList.size()){
            index = EnemyList.size();
        }
        for(int i=0; i<index; i++){
            EnemyList[i]->Update();
            EnemyList[i]->Draw();
            if(EnemyList[i]->IsDead()){
                m_player_money_now += EnemyList[i]->GiveMoney();
                EnemyHitCastle();
                EnemyList.erase(EnemyList.begin()+i);
                enemyTimeCounter -= 100;
                i -= 1;
                index -= 1;
            }
        }
    }

    // ---  Test for sm  ---
    //update swordsman
    // sm->Update();
    
}

// void Level1::End()  {}

void Level1::Draw()  {
    // 繪製地圖、路徑
    m_groundset1->Draw();
    m_pathset1->Draw();

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

    // ---  Test for sm  ---
    //draw swordsman
    // sm->Draw();
}