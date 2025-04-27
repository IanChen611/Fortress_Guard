#ifndef GUARD_HPP
#define GUARD_HPP

#include <string>

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

#include "Tile.hpp"
#include "Enemy.hpp"
#include "Button.hpp"


class Guard : public Util::GameObject {
public:
    Guard();
    ~Guard() = default;

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position);

    // 為了讓子類別(Swordsman之類的)可以Update
    void Update();

    virtual void Update_for_speccial_guard() = 0;

    virtual bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) = 0;

    void SetDeployed(bool isDeployed){m_isDeployed = isDeployed;}

    int GetCost(){return m_cost;}

    void SetEnemyInRange(std::shared_ptr<Enemy> enemy);

    bool IsEnemyInEnemyInRange(std::shared_ptr<Enemy> enemy){return std::find(m_enemyInRange.begin(), m_enemyInRange.end(), enemy) != m_enemyInRange.end();};

    void PopFrontEnemyInRange();

    void SetCanDeployed(bool canDeployed){m_canDeployed = canDeployed;}

    virtual void Upgrade() = 0;

    bool IsUpgraded(){return m_isUpgraded;}

    void SetIsUpgraded(bool isUpgraded){m_isUpgraded = isUpgraded;}

    int GetRank(){return m_rank;}

    void SetCanUpgrade(bool canUpgrade){m_canUpgrade = canUpgrade;}

    bool IsAttacker(){return m_isAttacker;}

    float GetDamage(){return m_damage;}

    bool IsAttackable(){return m_attackable;}

    void SetAttackable(bool attackable){m_attackable = attackable;}

protected:
    std::string m_myselfImagePath;
    std::string m_rangeImagePath;
    glm::vec2 m_coordinate;
    
    bool m_isDeployed = false;
    bool m_clickMe_RB = false;
    bool m_canDeployed = false;
    int m_cost;
    bool m_isAttacker = true;
    std::vector<glm::vec2> m_rangeCoordinate;
    std::vector<std::shared_ptr<Tile>> m_rangeTile;
    std::vector<std::shared_ptr<Enemy>> m_enemyInRange;

    // ------升級相關-------
    bool eliminated_deployed_problem = false;
    std::shared_ptr<Button> m_upgradeButton;
    bool m_clickMe_LB = false;
    bool m_clickMe_LB_down = false;
    int m_rank = 1;
    bool m_isUpgraded = false;
    bool m_canUpgrade = false;
    // 升級花費
    std::shared_ptr<Util::GameObject> m_upgradeCost;
    std::shared_ptr<Util::Text> m_upgradeCost_text;
    // 顯示等級的UI
    std::shared_ptr<Util::GameObject> m_ranknumber;
    std::shared_ptr<Util::Text> m_ranknumber_text;
    // ---------------------


    // 攻擊相關
    float m_damage;
    float m_attackTime = 100;
    float m_attackSpeed;
    bool m_attackable = false;
    bool m_isRange = false;
    std::shared_ptr<Util::GameObject> m_cooldown_bar;
    std::shared_ptr<Util::Image> m_cooldown_bar_IMG;
    float cooldown_bar_scale;
    int m_attackRange;

    // 子彈
    std::shared_ptr<Util::GameObject> bullet;
    bool bullet_flying = false;


    // 攻擊動畫
    bool attacking = false;
    int now_picture = 0;
    int picture_interval = 0;
    std::string attack_direction;
    std::vector<std::string> attackdown;
    std::vector<std::string> attackup;
    std::vector<std::string> attackleft;
    std::vector<std::string> attackright;
};

#endif