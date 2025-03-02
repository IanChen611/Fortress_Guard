#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "SceneManager.hpp"
#include "StartScene.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;
    auto startScene = std::make_unique<StartScene>();
    m_SceneManager.PushScene(std::move(startScene));
}

void App::Update() {
    //TODO: do your things here and delete this line <3
    m_SceneManager.Update();// 更新場景
    m_SceneManager.Draw();
    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
