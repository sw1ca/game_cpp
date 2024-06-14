#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Skeleton.h"
#include "Bullet.h"
#include "Boss.h"

class Player {
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
public:
    sf::Sprite playerSprite;
public:
    Player();
    ~Player();

    void Initialize();
    void Load();
    void Update(float deltaTime, std::vector<Enemy*>& enemies, sf::Vector2f& mousePosition);
    void Draw(sf::RenderWindow& window);
};



