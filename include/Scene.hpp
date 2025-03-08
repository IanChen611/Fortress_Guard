# ifndef SCENE_HPP
# define SCENE_HPP


class Scene{
public:
    Scene() = default;
    ~Scene() = default;
    virtual void Start() = 0; // 初始化
    virtual void Update() = 0; // 處理邏輯
    virtual void Draw() = 0; // 處理畫面
    virtual void End() = 0;
};


#endif // Scene_HPP