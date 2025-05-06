#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
#include "HealthPack.h"
#pragma once

class Map;
class Enemy;
class Player {
public:
    Player();
    ~Player();

    int health;
    sf::Sprite playerSprite;
    void Initialize();
    void Load();
    void Update(float deltaTime, std::vector<Enemy*>& enemies, sf::Vector2f& mousePosition, Map& map, sf::RenderWindow& window, std::vector<HealthPack>& healthPacks);
    void Draw(sf::RenderWindow& window);
    void ChangeHealth(int hp);

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
    sf::RectangleShape getBoundingRectanglePosition() const;
    sf::Vector2f getSize() const{
        return sf::Vector2f(playerSprite.getGlobalBounds().width, playerSprite.getGlobalBounds().height);
    }

    void Move(Map& map, sf::Vector2f direction, float deltaTime);
    void checkHealthPackCollision(std::vector<HealthPack>& healthPacks);
private:
    sf::Texture playerTexture;
    sf::Text healthText;
    sf::Font font;
    sf::Text gameOverText;
    std::vector<Bullet> bullets;

    float maxfireRate;
    float fireRateTimer;
    float playerSpeed;

    sf::RectangleShape boundingRectangle;
    sf::Vector2i size;
    sf::IntRect goUpTexture;
    sf::IntRect goDownTexture;
    sf::IntRect goLeftTexture;
    sf::IntRect goRightTexture;
};



