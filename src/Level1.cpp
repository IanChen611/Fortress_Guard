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
            m_ground[i][j] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_0.png");
            m_ground[i][j]->SetTouchable(true);
        }
    }
    m_groundset = std::make_shared<TileSet>(m_ground);
    m_groundset->SetAllZIndex(0);

    m_path[2][2] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_26_6.png");
    m_path[2][3] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_4.png");
    m_path[2][4] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[2][5] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[2][6] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[2][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_6.png");
    m_path[3][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[4][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[5][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[6][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[7][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_2_4.png");
    m_path[7][8] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[7][9] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[7][10] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[7][11] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[7][12] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[7][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_2_6.png");
    m_path[6][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[5][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[4][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_4.png");
    m_path[4][14] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[4][15] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[4][16] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_6.png");
    m_path[4][17] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_26_14.png");
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            if(m_path[i][j] != nullptr){
                m_ground[i][j]->SetTouchable(false);
            }
        }
    }
    m_pathset = std::make_shared<TileSet>(m_path);
    m_pathset->SetAllZIndex(1);
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
    // std::vector<std::vector<Enemy>> SumEnemy;
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
    // int wave = 1;
    // now_enemyList = SumEnemy[i-1];
}

Level1::~Level1() {
    LOG_INFO("Level1 destroyed");
}


// void Level1::Start() {
//     LOG_INFO("Scene1 Start");
// }

// void Level1::Update()  {
    // // 遊戲開始的倒數
    // if(startGameCounter < 300 && !gameStart){
    //     startGameCounter += 1;
    //     m_countdown_text->SetText(std::to_string(5 - startGameCounter/60));
    //     m_countdown_number->Draw();
    // }
    // else if(!gameStart){
    //     gameStart = true;
    //     m_countdown_number->SetVisible(false);
    //     LOG_INFO("Finish Countdown");
    // }

    // 地圖更新
    // m_groundset->Update();
    // m_pathset->Update();

    // // UI更新
    // for(auto ui : UI)
    // {
    //     ui->Update();
    // }
    
    // // 遊戲沒有輸(城堡扣完血) 且 遊戲沒有贏(敵人出動全部且沒有存在場上)
    // if(!gameLose && !gameWin){

    //     // 購買Guard的部分 更新
    //     if(buying){
    //         bt_cancelBuy->Update(); // 取消按鈕
    //         glm::vec2 mouse_pos = Util::Input::GetCursorPosition();
    //         int m_ground1_i = -(((int)mouse_pos.y+240+24)/48-10);
    //         int m_ground1_j = (((int)mouse_pos.x+480+24)/48);
    //         if(0 <= m_ground1_i && m_ground1_i < 10 && 0 <= m_ground1_j && m_ground1_j < 20){
    //             if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && m_ground1[m_ground1_i][m_ground1_j]->IsTouchable()){
    //                 if(m_player_money_now-tem->GetCost() >= 0){
    //                     m_ground1[m_ground1_i][m_ground1_j]->SetTouchable(false);
    //                     m_player_money_now -= tem->GetCost();
    //                     buying = false;
    //                     tem->SetDeployed(true);
    //                     GuardList.push_back(tem);
    //                     tem = nullptr;
    //                 }
    //             }
    //         }
    //     }
    //     if(tem != nullptr){
    //         if(cancelBuy){
    //             tem->~Guard();
    //             LOG_INFO("delete tem.");
    //             cancelBuy = false;
    //             buying = false;
    //             tem = nullptr;
    //         }
    //         else tem->Update();
    //     }

    //     //Guard 更新
    //     for(auto guard : GuardList){
    //         for(auto enemy : EnemyList){
    //             if(guard->IsEnemyInRange(enemy) && guard->IsEnemyInEnemyInRange(enemy)){
    //                 guard->SetEnemyInRange(enemy);
    //             }
    //             else if(!guard->IsEnemyInRange(enemy) && !guard->IsEnemyInEnemyInRange(enemy)){
    //                 guard->PopFrontEnemyInRange();
    //             }
    //         }
    //         guard->Update();
    //     }

    //     // 倒數結束後
    //     if(gameStart){
    //         //interval time after the third and the seventh enemy spawn 
    //         if(EnemyCounter != 3 && EnemyCounter != 7) {
    //             enemySpawnCounter += 1;
    //         }
    //         else{
    //             intervalCounter += 1;
    //             if(intervalCounter%intervalTime == 0){
    //                 EnemyCounter += 1;
    //                 enemyListIndex += 1;
    //                 spawnTime -= decreaseSpawnTimePerWaves;
    //             }
    //         }
    //         //spawn enemy after spawnTime
    //         if(enemySpawnCounter%spawnTime == 0) {
    //             EnemyCounter += 1;
    //             enemyListIndex += 1;
    //             enemySpawnCounter = 1;
    //         }
    //         //
    //         if(static_cast<std::size_t>(enemyListIndex) >= EnemyList.size()){
    //             enemyListIndex = EnemyList.size();
    //         }
    //         // 各個怪物 Update
    //         for(int i=0; i<enemyListIndex; i++){
    //             EnemyList[i]->Update();
    //             EnemyList[i]->Draw();
    //             //enemy died
    //             if(EnemyList[i]->IsDead()){
    //                 if(EnemyList[i]->GetHealth() > 0){
    //                     EnemyHitCastle();
    //                     if(!gameLose && !gameWin && m_castlehealth_now == 0) gameLose = true;
    //                 }
    //                 m_player_money_now += EnemyList[i]->GiveMoney();
    //                 EnemyList.erase(EnemyList.begin()+i);
    //                 i -= 1;
    //                 enemyListIndex -= 1;
    //             }
                
    //         }
    //         // 判斷是不是全部敵人都是dead
    //         bool allDead = true;
    //         for(auto enemy : EnemyList){
    //             allDead = enemy->IsDead();
    //         }
    //         if(allDead){
    //             gameWin = true;
    //         }

    //     }

    //     // ---  Test for sm  ---
    //     //update swordsman
    //     // sm->Update();
    // }
    // if(gameLose){
    //     img_gameFinish = std::make_shared<Util::GameObject>();
    //     img_gameFinish->SetZIndex(15);
    //     img_gameFinish->m_Transform.scale = {1.5f, 1.5f};
    //     img_gameFinish->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/GameLose.png"));
    // }
    // if(gameWin){
    //     img_gameFinish = std::make_shared<Util::GameObject>();
    //     img_gameFinish->SetZIndex(15);
    //     img_gameFinish->m_Transform.scale = {1.5f, 1.5f};
    //     img_gameFinish->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/GameWin.png"));
    // }
// }

// void Level1::End()  {}

// 處理這關特別邏輯
void Level1::Update_for_speccial_Level() {

}


// void Level1::Draw()  {
//     // 繪製地圖、路徑
//     m_groundset->Draw();
//     m_pathset->Draw();

//     // UI繪製
//     for(auto ui:UI)
//     {
//         ui->Draw();
//     }

    
//     // 購買Guard的部分 繪製
//     if(buying) bt_cancelBuy->Draw();
//     if(tem != nullptr) tem->Draw();

//     //Guard 繪製
//     for(auto guard : GuardList){
//         guard->Draw();
//     }

//     // 遊戲結束(贏、輸)的圖片
//     if(img_gameFinish != nullptr){
//         img_gameFinish->Draw();
//     }



//     // ---  Test for sm  ---
//     //draw swordsman
//     // sm->Draw();
// }


// 處理這關特別需要的畫面
void Level1::Draw_for_speccial_Level(){

}