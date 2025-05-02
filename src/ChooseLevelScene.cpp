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

        std::shared_ptr<Util::GameObject> tem1 = std::make_shared<Util::GameObject>();
        std::shared_ptr<Util::Image> tem_img = std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/chose_level_back.png");
        tem1->SetDrawable(tem_img);
        tem1->m_Transform.translation = {((((i - 1) % 5)*4)+2)*48 - 480, 240 - 48 * (3 * int(((i-1)/5)) + 2) + 6};
        tem1->m_Transform.scale = {0.5f, 0.5f};
        tem1->SetVisible(false);
        tem1->SetZIndex(-5);
        vec_Image.push_back(tem1);
    }

    //endless mode
    vec_Button.push_back(std::make_shared<Button>(RESOURCE_DIR"/Image/UI/test.png",
        0, -288, 16, 80, 5, 2,
        [this]() {this->OnClickLevelButton(999); })
    );

    vec_Button.push_back(std::make_shared<Button>(RESOURCE_DIR"/Image/UI/back.png",
        -437, 298, 170, 116, 0.5f, 0.5f,
        [this]() { 
            LOG_INFO("Clicked Back Button in ChoseLevelScene");
            this->OnClickBackPreScene();
    }));
}

void ChooseLevelScene::OnClickLevelButton(int i){
    LOG_INFO("Clicked the Level " + std::to_string(i));
    std::unique_ptr<Level> tem = std::make_unique<Level>(i);
    tem->SetSceneManager(m_SceneManager);
    m_SceneManager->PushScene(std::move(tem));
    
    // if(i == 1){
    //     LOG_INFO("Clicked the Level " + std::to_string(i));
    //     std::unique_ptr<Level> tem = std::make_unique<Level>(i);
    //     tem->SetSceneManager(m_SceneManager);
    //     m_SceneManager->PushScene(std::move(tem));
    // }
    // if(i == 2){
    //     LOG_INFO("Clicked the Level two");
    //     std::unique_ptr<Level2> tem = std::make_unique<Level2>();
    //     tem->SetSceneManager(m_SceneManager);
    //     m_SceneManager->PushScene(std::move(tem));
    // }
    // if(i == 3){
    //     LOG_INFO("Clicked the Level three");
    //     std::unique_ptr<Level3> tem = std::make_unique<Level3>();
    //     tem->SetSceneManager(m_SceneManager);
    //     m_SceneManager->PushScene(std::move(tem));
    // }
    // if(i == 4){
    //     LOG_INFO("Clicked the Level four");
    //     std::unique_ptr<Level4> tem = std::make_unique<Level4>();
    //     tem->SetSceneManager(m_SceneManager);
    //     m_SceneManager->PushScene(std::move(tem));
    // }
    // if(i == 5){
    //     LOG_INFO("Clicked the Level five");
    //     std::unique_ptr<Level5> tem = std::make_unique<Level5>();
    //     tem->SetSceneManager(m_SceneManager);
    //     m_SceneManager->PushScene(std::move(tem));
    // }
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
    glm::vec2 mouse_pos = Util::Input::GetCursorPosition();
    float img_Width = 182.0f / 2;
    float img_Height = 182.0f / 2;
    for(auto img : vec_Image){
        glm::vec2 m_Position = img->m_Transform.translation;
        if(mouse_pos.x >= (m_Position.x - img_Width/2) &&
            mouse_pos.x <= (m_Position.x + img_Width/2) &&
             mouse_pos.y >= (m_Position.y - img_Height/2) &&
            mouse_pos.y <= (m_Position.y + img_Height/2)){
                img->SetVisible(true);
            }
            else{
                img->SetVisible(false);
            }
    }
}

void ChooseLevelScene::Draw(){
    for(auto button : vec_Button){
        button->Draw();
    }
    for(auto img : vec_Image){
        img->Draw();
    }
}

// void ChooseLevelScene::End(){
//     LOG_INFO("ChoseLevelScene end");
// }