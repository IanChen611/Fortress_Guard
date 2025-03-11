# ifndef Level_HPP
# define Level_HPP

#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"
#include "Button.hpp"

class Level : public Scene{
public:
    Level() = default;
    ~Level() = default;
    // virtual void Start() = 0; // 初始化
    virtual void Update() = 0; // 處理邏輯
    virtual void Draw() = 0; // 處理畫面
    // virtual void End() = 0;
    void SetSceneManager(SceneManager *m_SceneManager){
        this->m_SceneManager = m_SceneManager;
    }
    void OnClickBackPreScene() override{
        m_SceneManager->PopScene();
    }
   


protected:
    SceneManager *m_SceneManager;
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
    void SetSceneManager(SceneManager *m_SceneManager){
        this->m_SceneManager = m_SceneManager;
    }
    void OnClickBackPreScene() override{
        m_SceneManager->PopScene();
    }

protected:
    std::vector<std::shared_ptr<Button>> UI;
    SceneManager *m_SceneManager;
};



#endif
