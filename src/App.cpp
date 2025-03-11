
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "App.hpp"
#include "Scene.hpp"
#include "Level.hpp"
#include "SceneManager.hpp"
#include "StartScene.hpp"
#include "Tile.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;
    
    std::vector<glm::vec2> waypoints = [()];
    m_Slime = std::make_shared<Enemy>(RESOURCE_DIR"/output_images/Slime/tile_0_0.png", waypoints, 8, 1);
    // m_Scene1 = std::make_unique<Scene1>();
}

void App::Update() {
    //TODO: do your things here and delete this line <3
    m_SceneManager.Update();// 更新場景
    m_SceneManager.Draw();
    // m_Scene1->Draw();
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
