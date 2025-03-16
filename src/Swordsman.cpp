#include "Swordsman.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"

Swordsman::Swordsman() {
    // m_myselfImagePath = RESOURCE_DIR"/output_images/Swordsman/tile_0_0.png";
    SetImage(RESOURCE_DIR"/output_images/Swordsman/tile_0_0.png");
    m_Transform.scale = {3, 3};
    SetZIndex(10);
    m_rangeImagePath = RESOURCE_DIR"/output_images/Tiles/tile_5_21.png";
    m_damage = 10;
    m_attackSpeed = 1.5;
    m_cost = 15;
    m_rangeCoordinate.push_back({0, 48});
    m_rangeCoordinate.push_back({0, -48});
    m_rangeCoordinate.push_back({-48, 0});
    m_rangeCoordinate.push_back({48, 0});
    m_rangeTile.push_back(std::make_shared<Tile>(m_rangeImagePath));
    m_rangeTile.push_back(std::make_shared<Tile>(m_rangeImagePath));
    m_rangeTile.push_back(std::make_shared<Tile>(m_rangeImagePath));
    m_rangeTile.push_back(std::make_shared<Tile>(m_rangeImagePath));
    LOG_INFO("Swordsman built");
}

void Swordsman::Update(){
    if(!m_isDeployed){
        glm::vec2 mouse_pos = Util::Input::GetCursorPosition();
        m_coordinate.x = (((int)mouse_pos.x+480+24)/48-10)*48;
        m_coordinate.y = (((int)mouse_pos.y+240+24)/48-5)*48;
        SetPosition(m_coordinate);
        for(int i=0; static_cast<std::size_t>(i) < m_rangeCoordinate.size(); i++){
            glm::vec2 tempCoordinate = {m_rangeCoordinate[i].x+m_coordinate.x, m_rangeCoordinate[i].y+m_coordinate.y};
            m_rangeTile[i]->SetZIndex(10);
            m_rangeTile[i]->SetPosition(tempCoordinate);
            m_rangeTile[i]->Draw();
        }
    }
}

bool Swordsman::IsEnemyInRange(const std::shared_ptr<Enemy> enemy){
    if(abs(enemy->m_Transform.translation.x-m_Transform.translation.x) <= 1 && abs(enemy->m_Transform.translation.y-m_Transform.translation.y) <= 1){
        return true;
    }
    else{
        return false;
    }
}