# ifndef STARTSCENE_HPP
# define STARTSCENE_HPP
#include "Scene.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"


class StartScene : public Scene {
public:
    void Start() override {
        LOG_INFO("StartScene Start");
        // 載入主選單資源、初始化介面
    }

    void Update() override {
        // 這裡放主選單場景的更新邏輯，如按下按鈕切換場景

        // 假設你想按下某個按鍵就切換到新場景
        // if (Util::Input::IsKeyUp(YOUR_KEY)) {
        //     // 切換場景 (需取得 SceneManager 或其他機制)
        // }
    }
    
    void Draw() override{
        // LOG_INFO("StartScene Draewd");
    }

    void End() override {
        LOG_INFO("StartScene End");
        // 請求釋放資源
    }

};
# endif // STARTSCENE_HPP