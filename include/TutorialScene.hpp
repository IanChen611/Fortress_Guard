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
    SceneManager *m_SceneManager;
};

#endif // TUTORIALSCENE_HPP