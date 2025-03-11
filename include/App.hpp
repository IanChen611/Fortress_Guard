#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "SceneManager.hpp"
#include "Scene.hpp"
#include "Tile.hpp"
#include "TileSet.hpp"
#include "Level.hpp"
#include "Enemy.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    SceneManager m_SceneManager;

    State m_CurrentState = State::START;

    std::shared_ptr<Enemy> m_Slime;
    std::unique_ptr<Level> m_Level1;
};

#endif
