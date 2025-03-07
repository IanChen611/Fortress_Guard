# ifndef STARTSCENE_HPP
# define STARTSCENE_HPP

#include "Scene.hpp"
#include "Tile.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"


class StartScene : public Scene {
public:
    StartScene();
    ~StartScene() override ;
    
    void Start() override ;

    void Update() override;
    
    void Draw() override ;

    void End() override ;
private:
    std::shared_ptr<Tile> m_Grass;
};
# endif // STARTSCENE_HPP