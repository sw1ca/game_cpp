#pragma once
#include "Enemy.h"

class Skeleton : public Enemy {
public:
    Skeleton();
    ~Skeleton();

    void Initialize() override;
    void Load() override;
    void Update(float deltaTime, const sf::Vector2f playerPosition, const sf::RectangleShape& playerShape, std::vector<Enemy*>& enemies) override;
    void Draw(sf::RenderWindow& window) override;
//    void shootingPlayer(const sf::Vector2f& playerPosition, const sf::RectangleShape& playerShape, float deltaTime) override;
private:
    sf::Sprite sprite;
//    Player &player;
//    void setPlayer(Player &player);
};

