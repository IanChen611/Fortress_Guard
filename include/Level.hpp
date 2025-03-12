# ifndef Level_HPP
# define Level_HPP

#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"
#include "Button.hpp"
#include "Enemy.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/GameObject.hpp"

class Level : public Scene{
public:
    Level(){
        // -----UI------
        // 返回前頁之按鈕
        UI.push_back(std::make_shared<Button>(RESOURCE_DIR"/Image/UI/back.png",
        -437, 298, 170, 116, 0.5f, 0.5f,
        [this]() { 
            this->OnClickBackPreScene();
        }));
        // 血量顯示
        m_castlehealth_ori = 5;
        m_castlehealth_now = m_castlehealth_ori;
        // UI.push_back(std::make_shared<Util::GameObject>());



        //
    }
    ~Level() = default;
    // virtual void Start() = 0; // 初始化
    virtual void Update() = 0; // 處理邏輯
    virtual void Draw() = 0; // 處理畫面
    // virtual void End() = 0;
    virtual void SpawnEnemies() = 0; // 生怪
    void SetSceneManager(SceneManager *m_SceneManager){
        this->m_SceneManager = m_SceneManager;
    }
    void OnClickBackPreScene() override{
        m_SceneManager->PopScene();
    }
   


protected:
    SceneManager *m_SceneManager;
    int m_castlehealth_ori;
    int m_castlehealth_now;
    std::vector<std::shared_ptr<Button>> UI;
    std::shared_ptr<Tile> m_ground1[10][20];
    std::shared_ptr<Tile> m_path1[10][20];
    std::shared_ptr<TileSet> m_groundset1;
    std::shared_ptr<TileSet> m_pathset1;
};

class Level1 : public Level {
public:
    Level1() ;
    ~Level1() ;
    void Start() override; // 初始化
    void Update() override; // 處理邏輯
    void Draw() override; // 處理畫面
    void End() override;
    void SpawnEnemies() override;

private:
    std::shared_ptr<Enemy> m_Slime;
    std::vector<glm::vec2> waypoints;
};





#endif
