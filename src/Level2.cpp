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

    m_path[2][3] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_26_6.png");
    
    m_path[4][17] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_26_14.png");
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