#include "StartScene.hpp"
#include "Tile.hpp"
#include "Button.hpp"
#include "ChooseLevelScene.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"

StartScene::StartScene() {
    LOG_INFO("StartScene built");
    m_StartButton = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/Button_StartGame.png",
                0, -150, 236, 88, 1, 1,
                [this]() { this->OnClickStartGame(); });
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



// void StartScene::Start(){
//     LOG_INFO("StartScene Start");
//     // 載入主選單資源、初始化介面
// }

void StartScene::Update(){
    m_StartButton->Update();
}

void StartScene::Draw() {
    m_StartButton->Draw();
    // LOG_INFO("StartScene Drawed");
}

// void StartScene::End() {
//     LOG_INFO("StartScene End");
//     // 請求釋放資源
// }