#include "StartScene.hpp"
#include "Tile.hpp"
#include "Button.hpp"
#include "ChooseLevelScene.hpp"
#include "TutorialScene.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"

StartScene::StartScene() {
    LOG_INFO("StartScene built");
    m_StartButton = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/Button_StartGame.png",
                0, -150, 236, 88, 1, 1,
                [this]() { this->OnClickStartGame(); });
    m_TutorialButton = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/Button_Tutorial.png",
                0, -245, 276, 120, 0.4f, 0.4f,
                [this]() { this->OnClickTutorial(); });

    for(int i=0;i<4;i++){
        // D:\OOP_Lab\Fortress_Guard\Resources\output_images\Chicken
        // 小雞動畫
        Chick_picture_movedown.push_back(RESOURCE_DIR"/output_images/Chick/tile_0_" + std::to_string(i) + ".png");
        Chick_picture_moveup.push_back(RESOURCE_DIR"/output_images/Chick/tile_1_" + std::to_string(i) + ".png");
        Chick_picture_moveright.push_back(RESOURCE_DIR"/output_images/Chick/tile_2_" + std::to_string(i) + ".png");
        Chick_picture_moveleft.push_back(RESOURCE_DIR"/output_images/Chick/tile_3_" + std::to_string(i) + ".png");
        // 大雞動畫
        Chicken_picture_movedown.push_back(RESOURCE_DIR"/output_images/Chicken/tile_0_" + std::to_string(i) + ".png");
        Chicken_picture_moveup.push_back(RESOURCE_DIR"/output_images/Chicken/tile_1_" + std::to_string(i) + ".png");
        Chicken_picture_moveleft.push_back(RESOURCE_DIR"/output_images/Chicken/tile_2_" + std::to_string(i) + ".png");
        Chicken_picture_moveright.push_back(RESOURCE_DIR"/output_images/Chicken/tile_3_" + std::to_string(i) + ".png");
    }
    LOG_INFO("file path is okay, Chick_picture_moveleft[0] => " + Chick_picture_moveleft[0]);
    // "D:\OOP_Lab\Fortress_Guard\Resources\output_images\Chick\tile_3_0.png"
    Chick = std::make_shared<Util::GameObject>();
    Chicken = std::make_shared<Util::GameObject>();

    std::shared_ptr<Util::Image> Chick_img = std::make_shared<Util::Image>(Chick_picture_moveleft[0]);
    Chick->SetDrawable(Chick_img);
    Chick->m_Transform.translation = {0.0f, 100.0f};
    Chick->m_Transform.scale = {3.0f, 3.0f};
    LOG_INFO("Chick built");

    Chicken->SetDrawable(std::make_shared<Util::Image>(Chicken_picture_moveleft[0]));
    Chicken->m_Transform.translation = {0.0f, 0.0f};
    Chicken->m_Transform.scale = {3.0f, 3.0f};
    LOG_INFO("Chicken built");
}

void StartScene::SetSceneManager(SceneManager *m_SceneManager){
    this->m_SceneManager = m_SceneManager;
}

StartScene::~StartScene() {
    LOG_INFO("StartScene destroyed");
}

void StartScene::OnClickStartGame() {
    LOG_INFO("Clicked Start Game");
    std::unique_ptr<ChooseLevelScene> tem = std::make_unique<ChooseLevelScene>();
    tem->SetSceneManager(m_SceneManager);
    m_SceneManager->PushScene(std::move(tem));
}

void StartScene::OnClickTutorial() {
    LOG_INFO("Clicked Tutorial");
    std::unique_ptr<TutorialScene> tem = std::make_unique<TutorialScene>();
    tem->SetSceneManager(m_SceneManager);
    m_SceneManager->PushScene(std::move(tem));
}



// void StartScene::Start(){
//     LOG_INFO("StartScene Start");
//     // 載入主選單資源、初始化介面
// }

void StartScene::Update(){
    m_StartButton->Update();
    m_TutorialButton->Update();

}

void StartScene::Draw() {
    m_StartButton->Draw();
    m_TutorialButton->Draw();
    Chick->Draw();
    Chicken->Draw();

    // LOG_INFO("StartScene Drawed");
}

// void StartScene::End() {
//     LOG_INFO("StartScene End");
//     // 請求釋放資源
// }