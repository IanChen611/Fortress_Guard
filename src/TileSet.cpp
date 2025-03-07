#include "TileSet.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

TileSet::TileSet(const std::shared_ptr<Tile> tiles[10][20]){
    for(int i=0; i<10; i++){
        for (int j=0; j<20; j++){
            m_tiles[i][j] = tiles[i][j];
        }
    }
    ResetPosition();
    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            m_tiles[i][j]->m_Transform.scale = {3, 3};
        }
    }
    LOG_INFO("TileSet built");
}

void TileSet::ResetPosition(){
    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            m_tiles[i][j]->SetPosition({-480.0f+48*j, 240.0f-48*i});
        }
    }
}

void TileSet::SetAllZIndex(int zindex){
    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            m_tiles[i][j]->SetZIndex(zindex);
        }
    }
}