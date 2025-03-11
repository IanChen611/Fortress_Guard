#ifndef CHOOSELEVELSCENE_HPP
#define CHOOSELEVELSCENE_HPP
#include <memory>
#include <vector>
#include <string>

#include "Scene.hpp"
#include "Tile.hpp"
#include "Button.hpp"
#include "SceneManager.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"


class ChooseLevelScene : public Scene {
public:
    ChooseLevelScene() ;
    ~ChooseLevelScene() = default;

    void Start() override;
    void Update() override;
    void Draw() override;
    void End() override;

    void OnClickLevelButton(int i);

    void SetSceneManager(SceneManager *scenemanager){
        this->m_SceneManager = scenemanager;
    }
private:
    SceneManager *m_SceneManager;
    std::vector<std::shared_ptr<Button>> vec_Button;

};


#endif
