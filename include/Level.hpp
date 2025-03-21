# ifndef LEVEL_HPP
# define LEVEL_HPP

#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"
#include "Button.hpp"
#include "Enemy.hpp"
#include "Heart.hpp"
#include "Ui.hpp"
#include "Money.hpp"
#include "Guard.hpp"
#include "Swordsman.hpp"
#include "Mage.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"

class Level : public Scene{
public:
    Level();
    ~Level() = default;
    // virtual void Start() = 0; // 初始化
    
    // 處理每關通用邏輯
    void Update() override; 
    // 處理特別需要的邏輯
    virtual void Update_for_speccial_Level() = 0;
    // 處理每關通用畫面
    void Draw() override; 
    // 處理個別需要之畫面
    virtual void Draw_for_speccial_Level() = 0;

    // virtual void End() = 0;


    void SetSceneManager(SceneManager *m_SceneManager);
    void OnClickBackPreScene() override ;

    void EnemyHitCastle();
    
    // virtual void GameStart() = 0;

    //按按鈕->角色跟著滑鼠動 1.->再按在地圖上一下放置角色(+扣錢)
    //                      2.->按取消按紐消失
    void OnClickBuyGuard(std::string characterName); // 按按鈕會call購買角色
    void OnClickCancelBuy();
    

protected:
    SceneManager *m_SceneManager;
    int m_castlehealth_ori = 5;
    int m_castlehealth_now;
    int m_player_money_ori = 30;
    int m_player_money_now;
    
    // UI介面存放的vector
    std::vector<std::shared_ptr<Ui>> UI;
    
    // 買角色跟角色vector
    std::shared_ptr<Button> bt_cancelBuy;
    std::shared_ptr<Guard> tem;
    bool buying = false;
    bool cancelBuy = false;
    std::vector<std::shared_ptr<Guard>> GuardList;



    // 敵人路線
    std::vector<glm::vec2> waypoints;

    // 敵人清單
    std::vector<std::shared_ptr<Enemy>> EnemyList;


    // --倒數的部分--
    int startGameCounter = 0;
    bool gameStart = false;
    std::shared_ptr<Util::GameObject> m_countdown_number; 
    std::shared_ptr<Util::Text> m_countdown_text; 
    
    // --生成敵人的計時器--
    int enemySpawnCounter = 0;
    int intervalCounter = 0;
    int EnemyCounter = 0;
    int spawnTime = 100;
    int intervalTime = 500;
    int decreaseSpawnTimePerWaves = 20;
    int enemyListIndex = 0;

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

class Level1 : public Level {
public:
    Level1() ;
    ~Level1() ;
    // void Start() override; // 初始化
    
    // 處理這關特別需要的邏輯
    void Update_for_speccial_Level() override;
    // 處理這關特別需要的畫面
    void Draw_for_speccial_Level() override; // 處理畫面
    // void End() override;

private:
    // std::shared_ptr<Tile> m_ground1[10][20];
    // std::shared_ptr<Tile> m_path1[10][20];
    // std::shared_ptr<TileSet> m_groundset1;
    // std::shared_ptr<TileSet> m_pathset1;

    // std::shared_ptr<Swordsman> sm;
    std::shared_ptr<Mage> mage;
};

#endif