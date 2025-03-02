# ifndef START_HPP
# define START_HPP


class Scene{
public:

    virtual void Start() = 0; // 初始化
    virtual void Update() = 0; // 處理邏輯
    virtual void Draw() = 0; // 處理畫面
    virtual void End() = 0;
};


#endif // START_HPP