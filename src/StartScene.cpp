#include "StartScene.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"

StartScene::StartScene() {
    LOG_INFO("StartScene built");
}
StartScene::~StartScene() {
    LOG_INFO("StartScene destroyed");
}

void StartScene::Start(){
    LOG_INFO("StartScene Start");
    // 載入主選單資源、初始化介面
}

void StartScene::Update() {
    // 這裡放主選單場景的更新邏輯，如按下按鈕切換場景

    // // 假設你想按下某個按鍵就切換到新場景
    // if (Util::Input::IsKeyUp(Util::Keycode::A)) {
    //     LOG_INFO("A key pressed");
    // }
}

void StartScene::Draw() {
    // LOG_INFO("StartScene Draewd");
}

void StartScene::End()  {
    LOG_INFO("StartScene End");
    // 請求釋放資源
}