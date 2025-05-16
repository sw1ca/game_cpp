#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "../core/Bullet.h"
#include "../config/EnemyConfig.h"

class Player;
class Enemy {
public:
    sf::Sprite sprite;
    int health;
    const int id;

    Enemy(Player& player, const EnemyConfig& config);
    virtual ~Enemy();

    virtual void initialize();
    virtual void load();
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window);

    void changeHealth(int hp);
    inline const sf::Rect<float> getGlobalBounds() const { return sprite.getGlobalBounds(); }
    bool checkPlayerDetectionCollision(const sf::RectangleShape& playerShape);
    void shootingPlayer(float deltaTime);
    bool isDead() const { return health <= 0; }
    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    virtual bool isBoss() const { return false; }
    void setPosition(sf::Vector2f& position) {
        sprite.setPosition(position);
    }
    int getId() const { return id; }
    void die() { health = 0; }

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
    static int nextId;
};