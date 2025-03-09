# ifndef STARTSCENE_HPP
# define STARTSCENE_HPP

#include "Scene.hpp"
#include "Tile.hpp"
#include "Button.hpp"
#include "SceneManager.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"


class StartScene : public Scene {
public:

    StartScene();
    ~StartScene() ;
    
    void SetSceneManager(SceneManager *m_SceneManager);

    void Start() override;
    void Update() override;
    void Draw() override;
    void End() override;

    void OnClickStartGame();
private:
    SceneManager *m_SceneManager;
    std::shared_ptr<Button> m_StartButton;
};
# endif // STARTSCENE_HPP