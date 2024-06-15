#pragma once
#include "Enemy.h"
#include "Player.h"

class Boss : public Enemy {
public:
    Boss(Player& player);
    ~Boss();

    void Initialize() override;
    void Load() override;
    void Update(float deltaTime, const sf::Vector2f playerPosition, const sf::RectangleShape& playerShape, std::vector<Enemy*>& enemies) override;
    void Draw(sf::RenderWindow& window) override;
//    void shootingPlayer(const sf::Vector2f& playerPosition, const sf::RectangleShape& playerShape, float deltaTime) override;
private:
    sf::Sprite sprite;
    Player &player;
//    void setPlayer(Player &player);
};


