#include "TutorialScene.hpp"


TutorialScene::TutorialScene(){
    Button_back = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/back.png",
        -437, 298, 170, 116, 0.5f, 0.5f,
        [this]() { 
            LOG_INFO("Clicked Back Button in Level1");
            this->OnClickBackPreScene();
    });
}

void TutorialScene::OnClickBackPreScene(){
    m_SceneManager->PopScene();
}

void TutorialScene::Update(){
    Button_back->Update();
}

void TutorialScene::Draw(){
    Button_back->Draw();
}
