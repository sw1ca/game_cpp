#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Bullet.h"
#include "GameStateManager.h"
#include "EnemyConfig.h"

class Player;
class Enemy {
public:
    sf::Sprite sprite;
    int health;

    Enemy(Player& player, const EnemyConfig& config);
    virtual ~Enemy();

    virtual void Initialize();
    virtual void Load();
    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow& window);

    void ChangeHealth(int hp);
    inline const sf::Rect<float> GetGlobalBounds() const { return sprite.getGlobalBounds(); }
    bool CheckPlayerDetectionCollision(const sf::RectangleShape& playerShape);
    void shootingPlayer(float deltaTime);

protected:
    Player* player;
    EnemyConfig config;
    sf::RectangleShape boundingRectangle;
    sf::RectangleShape detectionRectangle;
    sf::Text healthText;
    sf::Font font;

    sf::Texture texture;

    std::vector<Bullet> bullets;

    float maxFireRate;
    float fireRateTimer;
    int damage;
};