#include "pch.hpp"

#include "Level.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"

Level1::Level1(){
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
    //-----guard test-----
    // sm = std::make_shared<Swordsman>();
    // mage = std::make_shared<Mage>();
    //----生成敵人---放入道路----
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
}

Level1::~Level1() {
    LOG_INFO("Level1 destroyed");
}


// void Level1::Start() {
//     LOG_INFO("Scene1 Start");
// }



// void Level1::End()  {}

// 處理這關特別邏輯
void Level1::Update_for_speccial_Level() {
    
}

// 處理這關特別需要的畫面
void Level1::Draw_for_speccial_Level(){

}