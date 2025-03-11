#include "pch.hpp"

#include "Level.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"



Level1::Level1() {
    // UI 
    UI.push_back(std::make_shared<Button>(RESOURCE_DIR"/Image/UI/back.png",
    -437, 298, 170, 116, 0.5f, 0.5f,
    [this]() { 
        LOG_INFO("Clicked Back Button in Level1");
        this->OnClickBackPreScene();
    }));

    //

    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            m_ground1[i][j] = std::make_shared<Tile>(RESOURCE_DIR"/output_images/Tiles/tile_0_0.png");
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
    m_pathset1 = std::make_shared<TileSet>(m_path1);
    m_pathset1->SetAllZIndex(1);
    LOG_INFO("Level1 built");
}

Level1::~Level1() {
    LOG_INFO("Scene1 destroyed");
}


void Level1::Start() {
    LOG_INFO("Scene1 Start");
}

void Level1::Update()  {
    for(auto ui:UI)
    {
        ui->Update();
    }
    
}

void Level1::End()  {}

void Level1::Draw()  {
    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            m_ground1[i][j]->Draw();
            if(m_path1[i][j] != nullptr){
                m_path1[i][j]->Draw();
            }
        }
    }
    for(auto ui:UI)
    {
        ui->Draw();
    }
}
