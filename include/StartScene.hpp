# ifndef STARTSCENE_HPP
# define STARTSCENE_HPP

#include "Scene.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"


class StartScene : public Scene {
public:
    StartScene();
    ~StartScene() override ;
    
    void Start() override ;

    void Update() override;
    
    void Draw() override ;

    void End() override ;

};
# endif // STARTSCENE_HPP