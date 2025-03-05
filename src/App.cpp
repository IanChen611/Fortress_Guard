
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "App.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "StartScene.hpp"
#include "Tile.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;
    auto startScene = std::make_unique<StartScene>();
    m_SceneManager.PushScene(std::move(startScene));
    m_Grass = std::make_shared<Tile>("./output_images/Tiles/tile_0_0.png");
    // m_Grass->SetPosition({0.0f, 0.0f});
    // m_Grass->SetZIndex(0);
    // m_Grass->m_Transform.scale = {3, 3};
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
