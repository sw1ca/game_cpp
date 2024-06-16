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
    void Update(float deltaTime, std::vector<Enemy*>& enemies, sf::Vector2f& mousePosition, Map& map);
    void Draw(sf::RenderWindow& window);
    void ChangeHealth(int hp);

    sf::Vector2f getPosition() const;
    sf::RectangleShape getBoundingRectanglePosition() const;
    void setPosition(sf::Vector2f position);

    void Move(Map& map, sf::Vector2f direction, float deltaTime);
private:
    sf::Texture playerTexture;
    sf::Text healthText;
    sf::Font font;
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



