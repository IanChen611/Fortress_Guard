#ifndef TUTORIALSCENE_HPP
#define TUTORIALSCENE_HPP

#include "Scene.hpp"
#include "Button.hpp"
#include "SceneManager.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class TutorialScene : public Scene {
public:
    TutorialScene();
    ~TutorialScene() = default;

    // void Start() override;
    void Update() override;
    void Draw() override;
    // void End() override;


    void SetSceneManager(SceneManager *scenemanager){
        this->m_SceneManager = scenemanager;
    }

    void OnClickBackPreScene() override;
private:
    std::shared_ptr<Button> Button_back;

    std::shared_ptr<Button> next_page;
    std::shared_ptr<Button> pre_page;

    SceneManager *m_SceneManager;

    int now_page = 1;
    std::vector<std::shared_ptr<Util::GameObject>> vec_tutorial;
    std::shared_ptr<Util::GameObject> m_tutorial_1;
    std::shared_ptr<Util::GameObject> m_tutorial_2;
    std::shared_ptr<Util::GameObject> m_tutorial_3;
    std::shared_ptr<Util::GameObject> m_tutorial_4;
};

#endif // TUTORIALSCENE_HPP