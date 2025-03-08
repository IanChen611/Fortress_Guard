#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <memory>
#include <stack>
#include "Scene.hpp"
#include "Util/Logger.hpp"

class SceneManager {
public:
    SceneManager() ;
    ~SceneManager() = default;

    // 切換到新的場景（先把舊場景結束或暫存）
    void ChangeScene(std::unique_ptr<Scene> newScene) ;

    // 在舊場景上疊加新場景（如果要同時保留上一個場景狀態，可用這種方式）
    void PushScene(std::unique_ptr<Scene> newScene);

    // 回到上一個場景
    void PopScene();

    // 每次遊戲/程式主迴圈呼叫，用於更新當前的場景
    void Update();

    void Draw();

private:
    std::stack<std::unique_ptr<Scene>> m_Scenes;
};

#endif // SCENE_HPP
