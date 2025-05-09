#include <stdio.h>
#include <stdlib.h>

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
    // 隨機種子碼
    srand(time(NULL));

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
        Chick_picture_moveup.push_back(RESOURCE_DIR"/output_images/Chick/tile_0_" + std::to_string(i) + ".png");
        Chick_picture_movedown.push_back(RESOURCE_DIR"/output_images/Chick/tile_1_" + std::to_string(i) + ".png");
        Chick_picture_moveright.push_back(RESOURCE_DIR"/output_images/Chick/tile_2_" + std::to_string(i) + ".png");
        Chick_picture_moveleft.push_back(RESOURCE_DIR"/output_images/Chick/tile_3_" + std::to_string(i) + ".png");
        // 大雞動畫
        Chicken_picture_moveup.push_back(RESOURCE_DIR"/output_images/Chicken/tile_0_" + std::to_string(i) + ".png");
        Chicken_picture_movedown.push_back(RESOURCE_DIR"/output_images/Chicken/tile_1_" + std::to_string(i) + ".png");
        Chicken_picture_moveleft.push_back(RESOURCE_DIR"/output_images/Chicken/tile_2_" + std::to_string(i) + ".png");
        Chicken_picture_moveright.push_back(RESOURCE_DIR"/output_images/Chicken/tile_3_" + std::to_string(i) + ".png");
    }
    LOG_INFO("file path is okay, Chick_picture_moveleft[0] => " + Chick_picture_moveleft[0]);
    // "D:\OOP_Lab\Fortress_Guard\Resources\output_images\Chick\tile_3_0.png"
    Chick = std::make_shared<Util::GameObject>();
    Chicken = std::make_shared<Util::GameObject>();

    std::shared_ptr<Util::Image> Chick_img = std::make_shared<Util::Image>(Chick_picture_moveleft[0]);
    Chick->SetDrawable(Chick_img);
    Chick->SetZIndex(10);
    Chick->m_Transform.translation = {0.0f, 100.0f};
    Chick->m_Transform.scale = {4.0f, 4.0f};
    chick_to_x = rand() % 480 - 240;
    chick_to_y = rand() % 960 - 480;
    LOG_INFO("Chick built");

    Chicken->SetDrawable(std::make_shared<Util::Image>(Chicken_picture_moveleft[0]));
    Chicken->m_Transform.translation = {0.0f, 0.0f};
    Chicken->m_Transform.scale = {4.0f, 4.0f};
    Chicken->SetZIndex(10);
    chicken_to_x = rand() % 480 - 240;
    chicken_to_y = rand() % 960 - 480;
    LOG_INFO("Chicken built");

    // 按鈕背景
    std::shared_ptr<Util::GameObject> tem1 = std::make_shared<Util::GameObject>();
    std::shared_ptr<Util::Image> tem1_img = std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/chose_level_back.png");
    tem1->SetDrawable(tem1_img);
    tem1->m_Transform.translation = {0.0f, -150.0f};
    tem1->m_Transform.scale = {1.4f, 0.55f};
    tem1->SetVisible(false);
    tem1->SetZIndex(-5);
    vec_Img.push_back(tem1);

    // 按鈕背景
    std::shared_ptr<Util::GameObject> tem2 = std::make_shared<Util::GameObject>();
    std::shared_ptr<Util::Image> tem2_img = std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/chose_level_back.png");
    tem2->SetDrawable(tem2_img);
    tem2->m_Transform.translation = {0.0f, -245.0f};
    tem2->m_Transform.scale = {0.65f, 0.3f};
    tem2->SetVisible(false);
    tem2->SetZIndex(-5);
    vec_Img.push_back(tem2);
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
    // ----小雞行走----
    Chick_move();
    //-----------
    // ----大雞行走----
    Chicken_move();
    //-----------

    // 按鈕背景
    glm::vec2 mouse_pos = Util::Input::GetCursorPosition();
    for(auto img : vec_Img){
        float img_Width = img->GetScaledSize().x;
        float img_Height = img->GetScaledSize().y;
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

void StartScene::Draw() {
    m_StartButton->Draw();
    m_TutorialButton->Draw();
    Chick->Draw();
    Chicken->Draw();
    for(auto img : vec_Img){
        img->Draw();    
    }
    // LOG_INFO("StartScene Drawed");
}


void StartScene::Chick_move(){
    // ----小雞行走----
    float delta_x = chick_to_x - Chick->m_Transform.translation.x;
    float delta_y = chick_to_y - Chick->m_Transform.translation.y;
    float delta = std::sqrt(delta_x * delta_x + delta_y * delta_y);
    // 距離到了
    if(delta <= 10){
        chick_to_x = rand() % 480 - 240;
        chick_to_y = rand() % 960 - 480;
    }
    else{
        // 水平向量較多
        if(std::abs(delta_x) > std::abs(delta_y)){
            if(delta_x > 0){
                chick_mov_direction = "right";
            }
            else{
                chick_mov_direction = "left";
            }
        }
        // 鉛直向量較多
        else if(std::abs(delta_y) <= std::abs(delta_y)){
            if(delta_y > 0){
                chick_mov_direction = "down";
            }
            else{
                chick_mov_direction = "up";
            }
        }
        // 真實運動
        // LOG_INFO("chick_delat_x / chick_delat * chick_velocity = " + std::to_string(chick_delta_x / std::sqrt(chick_delat) * chick_velocity));
        Chick->m_Transform.translation.x += delta_x / delta * chick_velocity;
        Chick->m_Transform.translation.y += delta_y / delta * chick_velocity;
        // 動畫更新
        chick_picture_interval += 1;
        if(chick_picture_interval >= 5){
            chick_picture_interval = 0;
            chick_now_picture = (chick_now_picture + 1)%4;
            if(chick_mov_direction == "right"){
                Chick->SetDrawable(std::make_shared<Util::Image>(Chick_picture_moveright[chick_now_picture]));
            }
            if(chick_mov_direction == "left"){
                Chick->SetDrawable(std::make_shared<Util::Image>(Chick_picture_moveleft[chick_now_picture]));
            }
            if(chick_mov_direction == "up"){
                Chick->SetDrawable(std::make_shared<Util::Image>(Chick_picture_moveup[chick_now_picture]));
            }
            if(chick_mov_direction == "down"){
                Chick->SetDrawable(std::make_shared<Util::Image>(Chick_picture_movedown[chick_now_picture]));
            }
        }
    }
    //-----------
}

void StartScene::Chicken_move(){
    // ----大雞行走----
    float delta_x = chicken_to_x - Chicken->m_Transform.translation.x;
    float delta_y = (float)chicken_to_y - Chicken->m_Transform.translation.y;
    float delta = std::sqrt(delta_x * delta_x + delta_y * delta_y);
    if(delta <= 10){
        chicken_to_x = rand() % 480 - 240;
        chicken_to_y = rand() % 960 - 480;
    }
    else{
        // 水平向量較多
        if(std::abs(delta_x) > std::abs(delta_y)){
            if(delta_x > 0){
                chicken_mov_direction = "right";
            }
            else{
                chicken_mov_direction = "left";
            }
        }
        // 鉛直向量較多
        else if(std::abs(delta_x) <= std::abs(delta_y)){
            if(delta_y > 0){
                chicken_mov_direction = "down";
            }
            else{
                chicken_mov_direction = "up";
            }
        }
        // 真實運動
        Chicken->m_Transform.translation.x += delta_x / delta * chicken_velocity;
        Chicken->m_Transform.translation.y += delta_y / delta * chicken_velocity;
        // 動畫更新
        chicken_picture_interval += 1;
        if(chicken_picture_interval >= 5){
            chicken_picture_interval = 0;
            chicken_now_picture = (chicken_now_picture + 1)%4;
            if(chicken_mov_direction == "right"){
                Chicken->SetDrawable(std::make_shared<Util::Image>(Chicken_picture_moveright[chicken_now_picture]));
            }
            if(chicken_mov_direction == "left"){
                Chicken->SetDrawable(std::make_shared<Util::Image>(Chicken_picture_moveleft[chicken_now_picture]));
            }
            if(chicken_mov_direction == "up"){
                Chicken->SetDrawable(std::make_shared<Util::Image>(Chicken_picture_moveup[chicken_now_picture]));
            }
            if(chicken_mov_direction == "down"){
                Chicken->SetDrawable(std::make_shared<Util::Image>(Chicken_picture_movedown[chicken_now_picture]));
            }
        }
    }
    //-----------
}

// void StartScene::End() {
//     LOG_INFO("StartScene End");
//     // 請求釋放資源
// }