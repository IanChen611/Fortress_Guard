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

#include "Util/Logger.hpp"
#include "Util/Input.hpp"

class Level : public Scene{
public:
    Level();
    ~Level() = default;
    // virtual void Start() = 0; // 初始化
    virtual void Update() = 0; // 處理邏輯
    virtual void Draw() = 0; // 處理畫面
    // virtual void End() = 0;

    void SetSceneManager(SceneManager *m_SceneManager);
    void OnClickBackPreScene() override ;

    void EnemyHitCastle();

protected:
    SceneManager *m_SceneManager;
    int m_castlehealth_ori;
    int m_castlehealth_now;
    int m_player_money_ori;
    int m_player_money_now;
    std::vector<std::shared_ptr<Ui>> UI;
    std::vector<glm::vec2> waypoints;
    std::vector<std::shared_ptr<Enemy>> EnemyList;
    int enemyTimeCounter = 0;
    int spawnTime = 100;
    int enemyDropMoneyAmount = 30;
};

class Level1 : public Level {
public:
    Level1() ;
    ~Level1() ;
    // void Start() override; // 初始化
    void Update() override; // 處理邏輯
    void Draw() override; // 處理畫面
    // void End() override;

private:
    std::shared_ptr<Tile> m_ground1[10][20];
    std::shared_ptr<Tile> m_path1[10][20];
    std::shared_ptr<TileSet> m_groundset1;
    std::shared_ptr<TileSet> m_pathset1;
};

#endif