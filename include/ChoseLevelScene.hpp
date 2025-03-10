#ifndef CHOSELEVELSCENE_HPP
#define CHOSELEVELSCENE_HPP

#include "Scene.hpp"
#include "Tile.hpp"
#include "Button.hpp"
#include "SceneManager.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"


class ChoseLevelScene : public Scene {
public:
    ChoseLevelScene(){
        for(int i=1;i<=15;i++){
            vec_Button.push_back(std::make_share<Button>(RESOURCE_DIR"/Image/UI/" + i.to_string() + ".png"), 48, 48, 1, 1, );
        }
        
    }


private:
    std::vector<std::shared_ptr<Button>> vec_Button;
};



#endif