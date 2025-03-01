# pragma once
class Scene{
public:
    Scene(){
        Start();
    }
    virtual ~Scene(){
        End();
    }

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void End() = 0;
};
