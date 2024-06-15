#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Bullet.h"
#include "Player.h"

class Enemy {
public:
    Enemy(Player &player);
    virtual ~Enemy();

    virtual void Initialize();
    virtual void Load();
    virtual void Update(float deltaTime, const sf::Vector2f playerPosition, const sf::RectangleShape& playerShape, std::vector<Enemy*>& enemies);
    virtual void Draw(sf::RenderWindow& window);

    void ChangeHealth(int hp);
    inline sf::FloatRect GetGlobalBounds() const { return sprite.getGlobalBounds(); }
    bool CheckPlayerDetectionCollision(const sf::RectangleShape& playerShape);

    virtual void shootingPlayer(const sf::Vector2f& playerPosition, const sf::RectangleShape& playerShape, float deltaTime);

    int health;
protected:
    Player &player;
    sf::RectangleShape boundingRectangle;
    sf::RectangleShape detectionRectangle;
    sf::Text healthText;
    sf::Font font;
    sf::Sprite sprite;

    sf::Texture texture;
    sf::Vector2i shootingSize;
    sf::Vector2i detectionSize;
    sf::RectangleShape playerShape;

    std::vector<Bullet> bullets;
    float fireRateTimer;
    float maxFireRate;
};