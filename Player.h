#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Skeleton.h"
#include "Bullet.h"
class Player {
private:
    sf::Texture playerTexture;

    std::vector<Bullet> bullets;

    float maxfireRate;
    float fireRateTimer;
    float playerSpeed;

    sf::RectangleShape boundingRectangle;
    sf::Vector2i size;
public:
    sf::Sprite playerSprite;
public:
    Player();
    ~Player();

    void Initialize();
    void Load();
    void Update(float deltaTime, Skeleton& skeleton, sf::Vector2f& mousePosition);
    void Draw(sf::RenderWindow& window);
};



