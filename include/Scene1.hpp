# ifndef SCENE1_HPP
# define SCENE1_HPP

#include "Scene.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"

class Scene1 : public Scene{
public:
    Scene1();

    ~Scene1();
    
    void Start() override ;

    void Update() override;

    void End() override ;

    void Draw() override;

private:
    std::shared_ptr<Tile> m_ground1[10][20];
    std::shared_ptr<Tile> m_path1[10][20];
    std::shared_ptr<TileSet> m_groundset1;
    std::shared_ptr<TileSet> m_pathset1;
};


#endif