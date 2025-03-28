#include "Level.hpp"

Level3::Level3(){
    // ----取圖-----
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
    ReadMap readmap(3);
    LOG_INFO("Now enter iterator");
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            std::string tem = readmap.GiveTileName(i, j);
            // LOG_INFO(std::to_string(i) + ", " + std::to_string(j) + ":" + tem);
            if(tem.length() != 0){
                m_path[i][j] = std::make_shared<Tile>(tem);
                m_ground[i][j]->SetTouchable(false);
            }
        }
    }
    
    m_pathset = std::make_shared<TileSet>(m_path);
    m_pathset->SetAllZIndex(1);
    LOG_INFO("Level3 built");
    // ----圖載入結束-----
    
    //----道路-----
    waypoints.push_back({2, 2});
    waypoints.push_back({2, 7});
    waypoints.push_back({7, 7});
    waypoints.push_back({7, 13});
    waypoints.push_back({4, 13});
    waypoints.push_back({4, 17});
    waypoints.push_back({99999, 99999});
    ways.push_back(waypoints);
    waypoints.clear();
    //-----guard test-----
    // sm = std::make_shared<Swordsman>();
    // mage = std::make_shared<Mage>();
    //----生成敵人---放入道路----
    m_readenemy = std::make_shared<ReadEnemy>(ways, 1);
}

Level3::~Level3() {
    LOG_INFO("Level3 destroyed");
}

// 處理這關特別邏輯
void Level3::Update_for_speccial_Level() {
    
}

// 處理這關特別需要的畫面
void Level3::Draw_for_speccial_Level(){

}