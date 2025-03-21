#include "Scene.hpp"
#include "SceneManager.hpp"
#include "StartScene.hpp"

#include <memory>
#include <stack>

#include "Util/Logger.hpp"


SceneManager::SceneManager(){
    LOG_INFO("SceneManager built");
    auto m_startScene = std::make_unique<StartScene>();
    m_startScene->SetSceneManager(this);
    this->PushScene(std::move(m_startScene));
}

// 切換到新的場景（先把舊場景結束或暫存）
void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene) {
    if (!m_Scenes.empty()) {
        // 如果想要直接換場，先把頂端場景結束並清除
        // m_Scenes.top()->End();
        m_Scenes.pop();
    }
    m_Scenes.push(std::move(newScene));
    // m_Scenes.top()->Start();
}

// 在舊場景上疊加新場景（如果要同時保留上一個場景狀態，可用這種方式）
void SceneManager::PushScene(std::unique_ptr<Scene> newScene) {
    // LOG_INFO("PushScene be called");
    if (!m_Scenes.empty()) {
        // 也可以視需求暫停舊場景
    }
    m_Scenes.push(std::move(newScene));
    // m_Scenes.top()->Start();
}

// 回到上一個場景
void SceneManager::PopScene() {
    popingScene = true;
    // LOG_INFO("SceneManager::PopScene() be called");
    if (!m_Scenes.empty()) {
        // m_Scenes.top()->End();
        m_Scenes.pop();
        // LOG_INFO("Already pop now scene");
    }
    // LOG_INFO("Finish pop scene");
    popingScene = false;
}

// 每次遊戲/程式主迴圈呼叫，用於更新當前的場景
void SceneManager::Update() {
    // LOG_INFO("Updating First Scene");
    if (!m_Scenes.empty() && !popingScene) {
        m_Scenes.top()->Update();
    }
}

void SceneManager::Draw(){
    if (!m_Scenes.empty()) {
        m_Scenes.top()->Draw();
    }
}

void SceneManager::TestForBeCalled(){
    LOG_INFO("SceneManager::TestForBeCalled() be called");
}
