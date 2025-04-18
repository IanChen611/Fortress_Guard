#include "TutorialScene.hpp"


TutorialScene::TutorialScene(){
    Button_back = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/back.png",
        -480, 300, 170, 116, 0.5f, 0.5f,
        [this]() { 
            LOG_INFO("Clicked Back Button in TutorialPage");
            this->OnClickBackPreScene();
    });


    pre_page = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/back.png",
        -480, -300, 170, 116, 0.5f, 0.5f,
        [this]() { 
            LOG_INFO("Clicked next_page Button in TutorialPage");
            now_page -= 1;
            if(now_page < 1) now_page = 3;
    });

    next_page = std::make_shared<Button>(RESOURCE_DIR"/Image/UI/back.png",
        480, -300, 170, 116, 0.5f, 0.5f,
        [this]() { 
            LOG_INFO("Clicked pre_page Button in TutorialPage");
            now_page += 1;
            if(now_page > 3) now_page = 1;
    });
    next_page->m_Transform.rotation = 3.1415926f;
    
    m_tutorial_1 = std::make_shared<Util::GameObject>();
    std::shared_ptr<Util::Image> m_tutorial_1_img = std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/Tutorial_1.png");
    m_tutorial_1->SetDrawable(m_tutorial_1_img);
    m_tutorial_1->m_Transform.translation = {0, 0};
    m_tutorial_1->m_Transform.scale = {0.55f, 0.55f};
    m_tutorial_1->SetVisible(true);
    vec_tutorial.push_back(m_tutorial_1);

    m_tutorial_2 = std::make_shared<Util::GameObject>();
    std::shared_ptr<Util::Image> m_tutorial_2_img = std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/Tutorial_2.png");
    m_tutorial_2->SetDrawable(m_tutorial_2_img);
    m_tutorial_2->m_Transform.translation = {0, 0};
    m_tutorial_2->m_Transform.scale = {0.55f, 0.55f};
    m_tutorial_2->SetVisible(false);
    vec_tutorial.push_back(m_tutorial_2);


    m_tutorial_3 = std::make_shared<Util::GameObject>();
    std::shared_ptr<Util::Image> m_tutorial_3_img = std::make_shared<Util::Image>(RESOURCE_DIR"/Image/UI/Tutorial_3.png");
    m_tutorial_3->SetDrawable(m_tutorial_3_img);
    m_tutorial_3->m_Transform.translation = {0, 0};
    m_tutorial_3->m_Transform.scale = {0.55f, 0.55f};
    m_tutorial_3->SetVisible(false);
    vec_tutorial.push_back(m_tutorial_3);


}

void TutorialScene::OnClickBackPreScene(){
    m_SceneManager->PopScene();
}

void TutorialScene::Update(){
    Button_back->Update();
    next_page->Update();
    pre_page->Update();
    if(now_page == 1){
        m_tutorial_1->SetVisible(true);
        m_tutorial_2->SetVisible(false);
        m_tutorial_3->SetVisible(false);
    }
    else if(now_page == 2){
        m_tutorial_1->SetVisible(false);
        m_tutorial_2->SetVisible(true);
        m_tutorial_3->SetVisible(false);
    }
    else if(now_page == 3){
        m_tutorial_1->SetVisible(false);
        m_tutorial_2->SetVisible(false);
        m_tutorial_3->SetVisible(true);
    }
}

void TutorialScene::Draw(){
    Button_back->Draw();
    next_page->Draw();
    pre_page->Draw();
    for(auto to : vec_tutorial){
        to->Draw();
    }
}
