# ifndef STARTSCENE_HPP
# define STARTSCENE_HPP

#include "Scene.hpp"
#include "Tile.hpp"
#include "Button.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"


class StartScene : public Scene {
public:

    StartScene();
    ~StartScene() ;
    
    void Start() override;

    void Update() override;
    
    void Draw() override;

    void End() override;

    void OnClickStartGame();
private:
    std::shared_ptr<Button> m_StartButton;
};
# endif // STARTSCENE_HPP