#ifndef UI_HPP
#define UI_HPP


#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Ui : public Util::GameObject{
public:
    virtual void Update(){}
    void SetImage(const std::string& ImagePath){
        m_Drawable = std::make_shared<Util::Image>(ImagePath);
    }

};

#endif