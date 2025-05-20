# ifndef LEVEL_HPP
# define LEVEL_HPP

#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"
#include "Button.hpp"
#include "Enemy.hpp"
#include "Slime.hpp"
#include "Heart.hpp"
#include "Ui.hpp"
#include "Money.hpp"
#include "Guard.hpp"
#include "Swordsman.hpp"
#include "Mage.hpp"
#include "Musketeer.hpp"

#include "ReadMap.hpp"
#include "ReadEnemy.hpp"
#include "ShowMap.hpp"
#include "ReadWayPoint.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"

class Guard;

class Level : public Scene{
public:
    Level(int level);
    ~Level() = default;
    
    // 處理每關通用邏輯
    void Update() override; 
    // 處理每關通用畫面
    void Draw() override; 

    void SetSceneManager(SceneManager *m_SceneManager);
    
    void OnClickBackPreScene() override ;

    //按按鈕->角色跟著滑鼠動 1.->再按在地圖上一下放置角色(+扣錢)
    //                      2.->按取消按紐消失
    void OnClickBuyGuard(std::string characterName); // 按按鈕會call購買角色
    void OnClickCancelBuy();
    void OnClickChangeGameSpeed();
    
    // 自身是第幾關
    int m_level;

    int m_castlehealth_now;
    int m_player_money_now;

    std::vector<std::shared_ptr<Enemy>> enemyList;
    
    // 時間加速之記錄變數
    int gameSpeed = 1;

protected:
    SceneManager *m_SceneManager;
    int m_castlehealth_ori = 5;
    int m_player_money_ori = 100;

    // ShowMap
    bool all_showmap_finish = false;
    std::vector<std::shared_ptr<ShowMap>> m_showmap;
    
    // UI介面存放的vector
    std::vector<std::shared_ptr<Ui>> UI;
    bool pop_scene_next_frame = false;

    // 時間加速的按鈕
    std::shared_ptr<Button> m_TimeSpeed_Button;
    
    // 買角色跟角色vector
    std::shared_ptr<Button> bt_cancelBuy;
    std::shared_ptr<Guard> tem;
    bool buying = false;
    bool cancelBuy = false;
    std::vector<std::shared_ptr<Guard>> GuardList;



    // 敵人路線
    std::shared_ptr<ReadWayPoint> m_readwaypoint;
    std::vector<glm::vec2> waypoints;
    std::vector<std::vector<glm::vec2>> ways;
    std::shared_ptr<ReadEnemy> m_readenemy;

    // 敵人清單
    std::vector<std::pair<std::shared_ptr<Enemy>, int>> enemyPerWave;

    // 敵人波數
    int current_enemy_wave = 0;
    std::shared_ptr<Util::Text> m_current_enemy_wave_text;
    bool ready_to_next_wave = false;

    // --倒數的部分--
    int startGameCounter = 0;
    bool gameStart = false;
    std::shared_ptr<Util::GameObject> m_countdown_number; 
    std::shared_ptr<Util::Text> m_countdown_text; 
    
    // --生成敵人的計時器--
    int intervalCounter = 0;

    // 遊戲結束的部分
    bool gameLose = false;
    bool gameWin = false;
    std::shared_ptr<Util::GameObject> img_gameFinish;
    
    // 地圖跟路徑
    std::shared_ptr<Tile> m_ground[10][20];
    std::shared_ptr<Tile> m_path[10][20];
    std::shared_ptr<TileSet> m_groundset;
    std::shared_ptr<TileSet> m_pathset;
};

// class Level1 : public Level {
// public:
//     Level1() ;
//     ~Level1() ;
//     // void Start() override; // 初始化
    
//     // 處理這關特別需要的邏輯
//     void Update_for_speccial_Level() override;
//     // 處理這關特別需要的畫面
//     void Draw_for_speccial_Level() override; // 處理畫面
//     // void End() override;

// private:
// };

// class Level2 : public Level {
// public:
//     Level2() ;
//     ~Level2() ;
//     // void Start() override; // 初始化
    
//     // 處理這關特別需要的邏輯
//     void Update_for_speccial_Level() override;
//     // 處理這關特別需要的畫面
//     void Draw_for_speccial_Level() override; // 處理畫面
//     // void End() override;

// private:
// };

// class Level3 : public Level {
// public:
//     Level3() ;
//     ~Level3() ;
//     // void Start() override; // 初始化
    
//     // 處理這關特別需要的邏輯
//     void Update_for_speccial_Level() override;
//     // 處理這關特別需要的畫面
//     void Draw_for_speccial_Level() override; // 處理畫面
//     // void End() override;
    
// private:
// };

// class Level4 : public Level {
// public:
//     Level4() ;
//     ~Level4() ;
//     // void Start() override; // 初始化
    
//     // 處理這關特別需要的邏輯
//     void Update_for_speccial_Level() override;
//     // 處理這關特別需要的畫面
//     void Draw_for_speccial_Level() override; // 處理畫面
//     // void End() override;
    
// private:
// };

// class Level5 : public Level {
// public:
//     Level5() ;
//     ~Level5() ;
//     // void Start() override; // 初始化
    
//     // 處理這關特別需要的邏輯
//     void Update_for_speccial_Level() override;
//     // 處理這關特別需要的畫面
//     void Draw_for_speccial_Level() override; // 處理畫面
//     // void End() override;
    
// private:
// };


// class Level6 : public Level {
// public:
//     Level6() ;
//     ~Level6() ;
//     // void Start() override; // 初始化
    
//     // 處理這關特別需要的邏輯
//     void Update_for_speccial_Level() override;
//     // 處理這關特別需要的畫面
//     void Draw_for_speccial_Level() override; // 處理畫面
//     // void End() override;
        
//     private:
//     };

#endif