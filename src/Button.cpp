#include "Button.hpp"

#include "Util/Logger.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"

Button::Button(const std::string& imagePath, int posX, int posY, int width, int height, OnClickCallback onClick){
    m_X = posX;
    m_Y = posY;
    m_Transform.translation = glm::vec2(m_X, m_Y);
    m_Width = width;
    m_Height = height;
    m_OnClick = onClick;
    SetImage(imagePath);
}

void Button::Update()
{
    // 取得滑鼠位置
    glm::vec2 mouse_pos = Util::Input::GetCursorPosition();	


    bool inside = IsMouseInside(mouse_pos);
    bool mouseDown = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);   // 0 代表左鍵，可視情況改變
    bool mouseUp   = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);

    // 如果滑鼠在按鈕範圍內且被按下，就認定為「開始點擊」
    if (inside && mouseDown) {
        m_IsPressed = true;
    }

    // 如果原本處於「被按下」狀態，且又偵測到放開，同時滑鼠仍在按鈕上方，判定成功點擊
    if (m_IsPressed && mouseUp) {
        m_IsPressed = false;
        if (inside && m_OnClick) {
            // 呼叫 callback
            m_OnClick();
        }
    }

    // 如果滑鼠已經離開按鈕範圍，或是按住之後又移出去並放開，可以考慮重置 m_IsPressed
    if (!inside && mouseUp) {
        m_IsPressed = false;
    }
}

bool Button::IsMouseInside(glm::vec2 mousePos) const
{
    return (mousePos.x >= m_X &&
            mousePos.x <= (m_X + m_Width) &&
            mousePos.y >= m_Y &&
            mousePos.y <= (m_Y + m_Height));
}


void Button::SetImage(const std::string& ImagePath){
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}