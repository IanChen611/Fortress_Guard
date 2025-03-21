#include "pch.hpp"

#include "Level.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"

Level2::Level2(){
    // ----取圖-----
    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            m_ground[i][j] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_0.png");
            m_ground[i][j]->SetTouchable(true);
        }
    }
    m_groundset = std::make_shared<TileSet>(m_ground);
    m_groundset->SetAllZIndex(0);

    m_path[6][2] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_26_6.png");
    m_path[6][3] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_4.png");
    m_path[6][4] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[6][5] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[6][6] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[6][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[6][8] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[6][9] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[6][10] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[6][11] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_2_6.png");
    m_path[5][11] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[4][11] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_4.png");
    m_path[4][12] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[4][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[4][14] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[4][15] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[4][16] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[4][17] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_2_6.png");
    m_path[3][17] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[2][17] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[1][17] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_6.png");
    m_path[1][16] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[1][15] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[1][14] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[1][13] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[1][12] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_4.png");
    m_path[2][12] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_1_3.png");
    m_path[3][12] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_2_6.png");
    m_path[3][11] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[3][10] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[3][9] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[3][8] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[3][7] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[3][6] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[3][5] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[3][4] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_5.png");
    m_path[3][3] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_3_4.png");
    m_path[3][2] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_26_14.png");
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
    waypoints.push_back({6, 2});
    waypoints.push_back({6, 11});
    waypoints.push_back({4, 11});
    waypoints.push_back({4, 17});
    waypoints.push_back({1, 17});
    waypoints.push_back({1, 12});
    waypoints.push_back({3, 12});
    waypoints.push_back({3, 2});
    waypoints.push_back({99999, 99999});
    //----生成敵人---放入道路----
    EnemyList.push_back(std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1));
}

Level2::~Level2() {
    LOG_INFO("Level1 destroyed");
}

// 處理這關特別邏輯
void Level2::Update_for_speccial_Level() {
    
}

// 處理這關特別需要的畫面
void Level2::Draw_for_speccial_Level(){

}