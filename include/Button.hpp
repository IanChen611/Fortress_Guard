#ifndef BUTTON_HPP
#define BUTTON_HPP


#include <functional>
#include <string>

#include "Ui.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"    
#include "Util/Keycode.hpp"


class Button : public Ui{
public:
    using OnClickCallback = std::function<void()>;
    Button() = default;
    Button(const std::string& imagePath,
        int posX,
        int posY,
        float width,
        float height,
        float scaleX,
        float scaleY,
        OnClickCallback onClick);
    ~Button() = default;
    
    void Update() override;
    
    bool GetVisible() {return m_Visible;}

private:
    // 判斷滑鼠目前是否位於按鈕範圍內
    bool IsMouseInside(glm::vec2 mousePos) const;
    // 內部資料
    int m_X, m_Y;                 // 按鈕左上角座標
    float m_Width, m_Height;        // 按鈕大小
    bool m_IsPressed;             // 記錄滑鼠是否在按鈕上被按下
    OnClickCallback m_OnClick;    // Callback 函式
    std::string m_ImagePath;      // 圖片路逕
};


#endif
