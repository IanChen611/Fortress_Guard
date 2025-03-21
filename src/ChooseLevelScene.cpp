#include "ChooseLevelScene.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"

#include "Level.hpp"

ChooseLevelScene::ChooseLevelScene() {
    LOG_INFO("ChoseLevelScene built");
    for(int i=1; i<=15; i++){
        std::shared_ptr<Button> tem = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/" + std::to_string(i) + ".png",
            ((((i - 1) % 5)*4)+2)*48 - 480, 240 - 48 * (3 * int(((i-1)/5)) + 2), 110, 110, 0.6f, 0.6f,
            [this, i]() { this->OnClickLevelButton(i); });
        vec_Button.push_back(tem);
    }

    vec_Button.push_back(std::make_shared<Button>(RESOURCE_DIR"/Image/UI/back.png",
        -437, 298, 170, 116, 0.5f, 0.5f,
        [this]() { 
            LOG_INFO("Clicked Back Button in Level1");
            this->OnClickBackPreScene();
    }));
}

void ChooseLevelScene::OnClickLevelButton(int i){
    if(i == 1){
        LOG_INFO("Clicked the Level one");
        std::unique_ptr<Level1> tem = std::make_unique<Level1>();
        tem->SetSceneManager(m_SceneManager);
        m_SceneManager->PushScene(std::move(tem));
    }
    if(i == 2){
        LOG_INFO("Clicked the Level one");
        std::unique_ptr<Level2> tem = std::make_unique<Level2>();
        tem->SetSceneManager(m_SceneManager);
        m_SceneManager->PushScene(std::move(tem));
    }
}
void ChooseLevelScene::OnClickBackPreScene(){
    m_SceneManager->PopScene();
}


// void ChooseLevelScene::Start(){
//     LOG_INFO("ChoseLevelScene Start");
// }


void ChooseLevelScene::Update(){
    for(auto button : vec_Button){
        button->Update();
    }
}

void ChooseLevelScene::Draw(){
    for(auto button : vec_Button){
        button->Draw();
    }
}

// void ChooseLevelScene::End(){
//     LOG_INFO("ChoseLevelScene end");
// }