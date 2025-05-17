#pragma once

#include <memory>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "../core/Bullet.h"
#include "Enemy.h"
#include "../map/Map.h"
#include "../items/HealthElixir.h"
#include "../items/StrengthElixir.h"
#pragma once

class Map;
class Enemy;
class Player {
public:
    Player();
    ~Player();


    sf::Sprite playerSprite;
    void initialize();
    void load();
    void update(float deltaTime, std::vector<Enemy*>& enemies, sf::Vector2f& mousePosition, Map& map, sf::RenderWindow& window, std::vector<std::unique_ptr<Elixir>>& elixirs);
    void draw(sf::RenderWindow& window);
    void changeHealth(int hp);

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
    sf::RectangleShape getBoundingRectanglePosition() const;
    sf::Vector2f getSize() const{
        return sf::Vector2f(playerSprite.getGlobalBounds().width, playerSprite.getGlobalBounds().height);
    }

    void move(Map& map, sf::Vector2f direction, float deltaTime);
    void checkElixirCollision(std::vector<std::unique_ptr<Elixir>>& elixirs);
    void setHealth(int newHealth);
    int getHealth() const;

private:
    sf::Texture playerTexture;
    sf::Text healthText;
    sf::Font font;
    sf::Text gameOverText;
    std::vector<Bullet> bullets;

    int health;
    float maxfireRate;
    float fireRateTimer;
    float playerSpeed;
    int bulletDamage = 10;

    sf::RectangleShape boundingRectangle;
    sf::Vector2i size;
    sf::IntRect goUpTexture;
    sf::IntRect goDownTexture;
    sf::IntRect goLeftTexture;
    sf::IntRect goRightTexture;
};



