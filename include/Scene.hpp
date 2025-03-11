# ifndef SCENE_HPP
# define SCENE_HPP

class SceneManager;

class Scene{
public:
    Scene() = default;
    Scene(SceneManager* m_SceneManager) : m_SceneManager(m_SceneManager){}
    void SetSceneManager(SceneManager* m_SceneManager){
        this->m_SceneManager = m_SceneManager;
    }
    ~Scene() = default;
    virtual void Start() = 0; // 初始化
    virtual void Update() = 0; // 處理邏輯
    virtual void Draw() = 0; // 處理畫面
    virtual void End() = 0;
    virtual void OnClickBackPreScene() = 0;

protected:
    SceneManager* m_SceneManager;
};


#endif // Scene_HPP
