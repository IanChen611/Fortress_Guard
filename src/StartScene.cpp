#include "StartScene.hpp"
#include "Tile.hpp"
#include "Button.hpp"
#include "ChooseLevelScene.hpp"
#include "TutorialScene.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"

StartScene::StartScene() {
    LOG_INFO("StartScene built");
    m_StartButton = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/Button_StartGame.png",
                0, -150, 236, 88, 1, 1,
                [this]() { this->OnClickStartGame(); });
    m_TutorialButton = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/Button_Tutorial.png",
                0, -245, 276, 120, 0.4f, 0.4f,
                [this]() { this->OnClickTutorial(); });
}

void StartScene::SetSceneManager(SceneManager *m_SceneManager){
    this->m_SceneManager = m_SceneManager;
}

StartScene::~StartScene() {
    LOG_INFO("StartScene destroyed");
}

void StartScene::OnClickStartGame() {
    LOG_INFO("Clicked Start Game");
    std::unique_ptr<ChooseLevelScene> tem = std::make_unique<ChooseLevelScene>();
    tem->SetSceneManager(m_SceneManager);
    m_SceneManager->PushScene(std::move(tem));
}

void StartScene::OnClickTutorial() {
    LOG_INFO("Clicked Tutorial");
    std::unique_ptr<TutorialScene> tem = std::make_unique<TutorialScene>();
    tem->SetSceneManager(m_SceneManager);
    m_SceneManager->PushScene(std::move(tem));
}



// void StartScene::Start(){
//     LOG_INFO("StartScene Start");
//     // 載入主選單資源、初始化介面
// }

void StartScene::Update(){
    m_StartButton->Update();
    m_TutorialButton->Update();
}

void StartScene::Draw() {
    m_StartButton->Draw();
    m_TutorialButton->Draw();

    // LOG_INFO("StartScene Drawed");
}

// void StartScene::End() {
//     LOG_INFO("StartScene End");
//     // 請求釋放資源
// }