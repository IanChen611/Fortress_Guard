#pragma once
#include <memory>
#include <stack>
#include "Scene.hpp"

class SceneManager {
public:
    // 切換到新的場景（先把舊場景結束或暫存）
    void ChangeScene(std::unique_ptr<Scene> newScene) {
        if (!m_Scenes.empty()) {
            // 如果想要直接換場，先把頂端場景結束並清除
            m_Scenes.top()->End();
            m_Scenes.pop();
        }
        m_Scenes.push(std::move(newScene));
        m_Scenes.top()->Start();
    }

    // 在舊場景上疊加新場景（如果要同時保留上一個場景狀態，可用這種方式）
    void PushScene(std::unique_ptr<Scene> newScene) {
        if (!m_Scenes.empty()) {
            // 也可以視需求暫停舊場景
        }
        m_Scenes.push(std::move(newScene));
        m_Scenes.top()->Start();
    }

    // 回到上一個場景
    void PopScene() {
        if (!m_Scenes.empty()) {
            m_Scenes.top()->End();
            m_Scenes.pop();
        }
        if (!m_Scenes.empty()) {
            // 回到上一個場景，可以視需求恢復它
        }
    }

    // 每次遊戲/程式主迴圈呼叫，用於更新當前的場景
    void Update() {
        if (!m_Scenes.empty()) {
            m_Scenes.top()->Update();
        }
    }

private:
    std::stack<std::unique_ptr<Scene>> m_Scenes;
};
