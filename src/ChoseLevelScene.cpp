#include "ChoseLevelScene.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"

#include "Level.hpp"

ChoseLevelScene::ChoseLevelScene() {
    LOG_INFO("ChoseLevelScene built");
    for(int i=1; i<=15; i++){
        std::shared_ptr<Button> tem = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/" + std::to_string(i) + ".png",
            (i % 5)*48-24 - 480, 240 - 48 * 3 * int(((i-1)/5)), 48, 48, 1.0f, 1.0f,
            [this, i]() { this->OnClickLevelButton(i); });
        vec_Button.push_back(tem);
    }
}

void ChoseLevelScene::OnClickLevelButton(int i){
    if(i == 1){
        LOG_INFO("Clicked the Level one");
        std::unique_ptr<Level1> tem = std::make_unique<Level1>();
        tem->SetSceneManager(m_SceneManager);
        m_SceneManager->ChangeScene(std::move(tem));
    }
}

void ChoseLevelScene::Update(){
    for(auto button : vec_Button){
        button->Update();
    }
}

void ChoseLevelScene::Draw(){
    for(auto button : vec_Button){
        button->Draw();
    }
}
