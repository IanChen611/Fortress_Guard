# ifndef Level_HPP
# define Level_HPP

#include "Scene.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"

class Level : public Scene{
public:
    Level() = default;
    ~Level() = default;
    virtual void Start() = 0; // 初始化
    virtual void Update() = 0; // 處理邏輯
    virtual void Draw() = 0; // 處理畫面
    virtual void End() = 0;

protected:
    std::shared_ptr<Tile> m_ground1[10][20];
    std::shared_ptr<Tile> m_path1[10][20];
    std::shared_ptr<TileSet> m_groundset1;
    std::shared_ptr<TileSet> m_pathset1;
};


#endif