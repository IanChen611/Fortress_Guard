#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "ReadMap.hpp"

#include "Util/Logger.hpp"


ReadMap::ReadMap(int level){
    std::string fileName = RESOURCE_DIR"/Map/Level" + std::to_string(level) + ".csv";
    file.open(fileName);
    if (!file.is_open()) {
        LOG_INFO("The file Level" + std::to_string(level) + ".csv cannot be opened.");
        return;
    }
    if(file.is_open()){
        LOG_INFO("The file Level" + std::to_string(level) + ".csv is opened.");
    }
    /*
    G1 => 草地
    E1 => 敵人城堡
    C1 => 自家城堡
    T1 => 左到下的轉彎
    T2 => 下到右的轉彎
    T3 => 右到上的轉彎
    T4 => 上到左的轉彎
    S1 => 水平的直走
    S2 => 鉛直的直走
    SR => 起點向右
    SU => 起點向上 *
    SL => 起點向左 *
    SD => 起點向下 *
    */
    std::string line;
    int i = -1;
    while(getline(file, line)){
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;
        int j = -1;
        i++;
        while(getline(lineStream, cell, ',')){
            std::string temp;
            j++;
            //  Work!!
            LOG_INFO(std::to_string(i) + ", " + std::to_string(j)+ ": " + cell);
            if(cell == "N"){
                temp = "";
            }
            // LOG_INFO(cell);
            // LOG_INFO(cell)
            // 草地
            else if(cell[0] == 'G'){
                if(cell[1] == '1'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_0_0.png";
                }
            }
            // 敵人城堡
            else if(cell[0] == 'E'){
                if(cell[1] == '1'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_26_6.png";
                }
            }
            // 自家城堡
            else if(cell[0] == 'C'){
                if(cell[1] == '1'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_26_14.png";
                }
            }
            // 轉彎
            else if(cell[0] == 'T'){
                // 左到下的轉彎
                if(cell[1] == '1'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_0_6.png";
                }
                // 下到右的轉彎
                else if(cell[1] == '2'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_0_4.png";
                }
                // 右到上的轉彎
                else if(cell[1] == '3'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_2_4.png";
                }
                // 上到左轉彎
                else if(cell[1] == '4'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_2_6.png";
                }
            }
            // 直走
            else if(cell[0] == 'S'){
                // 水平的直走
                if(cell[1] == '1'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_3_5.png";
                }
                // 鉛直的直走
                if(cell[1] == '2'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_1_3.png";
                }
                // 起點向右
                if(cell[1] == 'R'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_3_4.png";
            
                }
                if(cell[1] == 'L'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_3_6.png";
                }
            }
            row.push_back(temp);
        }
        map.push_back(row);
    }
}

ReadMap::~ReadMap(){
    file.close();
}

