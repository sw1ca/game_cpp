#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
//#include "Skeleton.h"
#include "Bullet.h"
//#include "Boss.h"
#include "Enemy.h" // Include the full definition of the Enemy class
class Enemy; // Forward declaration of Enemy class
class Player {
public:
    Player();
    ~Player();

    sf::Sprite playerSprite;
    void Initialize();
    void Load();
    void Update(float deltaTime, std::vector<Enemy*>& enemies, sf::Vector2f& mousePosition);
    void Draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    sf::RectangleShape getBoundingRectanglePosition() const;
private:
    sf::Texture playerTexture;

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



