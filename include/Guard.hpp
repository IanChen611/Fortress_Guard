#ifndef GUARD_HPP
#define GUARD_HPP

#include <string>

#include "Util/GameObject.hpp"

#include "Tile.hpp"
#include "Enemy.hpp"

class Guard : public Util::GameObject {
public:
    Guard() = default;
    ~Guard() = default;

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    // 為了讓子類別(Swordsman之類的)可以Update
    virtual void Update(){}

    virtual bool IsEnemyInRange(const std::shared_ptr<Enemy> enemy) = 0;

    void SetDeployed(bool isDeployed){m_isDeployed = isDeployed;}

    int GetCost(){return m_cost;}

    void SetEnemyInRange(std::shared_ptr<Enemy> enemy){m_enemyInRange.push_back(enemy);}

    bool IsEnemyInEnemyInRange(std::shared_ptr<Enemy> enemy){return std::find(m_enemyInRange.begin(), m_enemyInRange.end(), enemy) == m_enemyInRange.end();};

    void PopFrontEnemyInRange(std::shared_ptr<Enemy> enemy){m_enemyInRange.erase(m_enemyInRange.begin());}

protected:
    std::string m_myselfImagePath;
    std::string m_rangeImagePath;
    glm::vec2 m_coordinate;
    int m_damage;
    float m_attackSpeed;
    bool m_isDeployed = false;
    int m_cost;
    std::vector<glm::vec2> m_rangeCoordinate;
    std::vector<std::shared_ptr<Tile>> m_rangeTile;
    std::vector<std::shared_ptr<Enemy>> m_enemyInRange;
};

#endif