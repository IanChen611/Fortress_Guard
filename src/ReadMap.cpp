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
    N、G1 => 草地
    TR => 單棵樹
    E1 => 敵人城堡
    C1 => 自家城堡
    T1 => 左下的轉彎
    T2 => 右下的轉彎
    T3 => 右上的轉彎
    T4 => 左上的轉彎
    RL => 沒有向左的三岔路
    RR => 沒有向右的三岔路
    RU => 沒有向上的三岔路
    RD => 沒有向下的三岔路
    RA => 十字路口
    S1 => 水平的直走
    S2 => 鉛直的直走
    SR => 起點向右
    SU => 起點向上 
    SL => 起點向左
    SD => 起點向下 
    W1 => 水
    WU => 水 + 上面邊界 
    WD => 水 + 下面邊界 
    WR => 水 + 右邊邊界 
    WL => 水 + 左邊邊界 
    W2 => 水 + 上面右邊邊界 
    W3 => 水 + 上面左邊邊界 
    W4 => 水 + 下面右邊邊界 
    W5 => 水 + 下面左邊邊界 
    W6 => 水 + 右上一點島嶼
    W8 => 水 + 左上一點島嶼
    W7 => 水 + 右下一點島嶼
    W9 => 水 + 左下一點島嶼
    WI => 水上面有島 
    PU => 木棧板上方銜接陸地
    PD => 木棧板下方銜接陸地
    PR => 木棧板右方銜接陸地
    PL => 木棧板左方銜接陸地
    PH => 木棧板水平直走
    PV => 木棧板垂直直走
    PA => 木棧板十字路口
    P1 => 沒有向左的三岔木棧板
    P2 => 沒有向右的三岔木棧板
    P3 => 沒有向上的三岔木棧板
    P4 => 沒有向下的三岔木棧板
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
            std::string temp = "";
            j++;
            //  Work!!
            // LOG_INFO(std::to_string(i) + ", " + std::to_string(j)+ ": " + cell);
            if(cell[0] == 'N'){
                temp = "";
            }
            // LOG_INFO(cell);
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
            // 轉彎 + 樹
            else if(cell[0] == 'T'){
                // 樹
                if(cell[1] == 'R'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_9_8.png";
                }
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
            //路口
            else if(cell[0] == 'R'){
                //no left
                if(cell[1] == 'L'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_1_4.png";
                }
                //no right
                else if(cell[1] == 'R'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_1_6.png";
                }
                //no up
                else if(cell[1] == 'U'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_0_5.png";
                }
                //no down
                else if(cell[1] == 'D'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_2_5.png";
                }
                //cross-road
                else if(cell[1] == 'A'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_1_5.png";
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
                // 起點向左
                if(cell[1] == 'L'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_3_6.png";
                }
                // 起點向上
                if(cell[1] == 'U'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_2_3.png";
                }
                // 起點向下
                if(cell[1] == 'D'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_0_3.png";
                }
            }
            // 水相關
            else if(cell[0] == 'W'){
                // 單純水
                if(cell[1] == '1'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_14_8.png";
                }
                // 水 + 上面邊界
                if(cell[1] == 'U'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_13_8.png";
                }
                // 水 + 下面邊界
                if(cell[1] == 'D'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_15_8.png";
                }
                // 水 + 右邊邊界
                if(cell[1] == 'R'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_14_9.png";
                }
                // 水 + 左邊邊界
                if(cell[1] == 'L'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_14_7.png";
                }
                // 水 + 上面右邊邊界 
                if(cell[1] == '2'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_13_9.png";
                }
                // 水 + 上面左邊邊界 
                if(cell[1] == '3'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_13_7.png";
                }
                // 水 + 下面右邊邊界 
                if(cell[1] == '4'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_15_9.png";
                }
                // 水 + 下面左邊邊界 
                if(cell[1] == '5'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_15_7.png";
                }
                // 水 + 右上一點島嶼 
                if(cell[1] == '6'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_14_11.png";
                }
                // 水 + 右下一點島嶼 
                if(cell[1] == '7'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_13_11.png";
                }
                // 水 + 左上一點島嶼 
                if(cell[1] == '8'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_14_10.png";
                }
                // 水 + 左下一點島嶼 
                if(cell[1] == '9'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_13_10.png";
                }
                

                // 水 + 島
                if(cell[1] == 'I'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_14_5.png";
                }
            }
            // 木棧板系列
            else if(cell[0] == 'P'){
                // PU => 木棧板上方銜接陸地
                if(cell[1] == 'U'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_30_10.png";
                }
                // PD => 木棧板下方銜接陸地
                if(cell[1] == 'D'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_32_10.png";
                }
                // PR => 木棧板右方銜接陸地
                if(cell[1] == 'R'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_32_13.png";
                }
                // PL => 木棧板左方銜接陸地
                if(cell[1] == 'L'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_32_11.png";
                }
                // PH => 木棧板水平直走
                if(cell[1] == 'H'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_32_12.png";
                }
                // PV => 木棧板垂直直走
                if(cell[1] == 'V'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_31_10.png";
                }
                if(cell[1] == 'A'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_27_23.png";
                }
                // P1 => 沒有向左的三岔木棧板
                if(cell[1] == '1'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_27_22.png";
                }
                // P2 => 沒有向右的三岔木棧板
                if(cell[1] == '2'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_27_24.png";
                }
                // P3 => 沒有向上的三岔木棧板
                if(cell[1] == '3'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_26_23.png";
                }
                // P4 => 沒有向下的三岔木棧板
                if(cell[1] == '4'){
                    temp = RESOURCE_DIR"/output_images/Tiles/tile_28_23.png";
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

