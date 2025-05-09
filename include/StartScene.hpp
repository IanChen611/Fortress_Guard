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
    
    void SetSceneManager(SceneManager *scenemanager);

    // void Start() override;
    void Update() override;
    void Draw() override;
    // void End() override;

    void OnClickStartGame();
    void OnClickTutorial();
    void OnClickBackPreScene() override {}
    void Chick_move();
    void Chicken_move();

private:
    SceneManager *m_SceneManager;
    std::shared_ptr<Button> m_StartButton;
    std::shared_ptr<Button> m_TutorialButton;
    // ------角色 and 動畫------
    // 小雞
    float chick_to_x;
    float chick_to_y;
    int chick_velocity = 7;
    std::shared_ptr<Util::GameObject> Chick;

    std::string chick_mov_direction = "left";
    int chick_now_picture = 0;
    int chick_picture_interval = 0;
    std::vector<std::string> Chick_picture_moveright;
    std::vector<std::string> Chick_picture_moveleft;
    std::vector<std::string> Chick_picture_moveup;
    std::vector<std::string> Chick_picture_movedown;

    // 大雞
    float chicken_to_x;
    float chicken_to_y;
    int chicken_velocity = 4;
    std::shared_ptr<Util::GameObject> Chicken;

    std::string chicken_mov_direction = "left";
    int chicken_now_picture = 0;
    int chicken_picture_interval = 0;
    std::vector<std::string> Chicken_picture_moveright;
    std::vector<std::string> Chicken_picture_moveleft;
    std::vector<std::string> Chicken_picture_moveup;
    std::vector<std::string> Chicken_picture_movedown;
    // ------------------------------------------
};
# endif // STARTSCENE_HPP