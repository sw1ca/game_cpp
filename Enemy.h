#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Enemy {
public:
    Enemy();
    virtual ~Enemy();

    virtual void Initialize();
    virtual void Load();
    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow& window);

    void ChangeHealth(int hp);

    sf::Sprite sprite;
    int health;
protected:
    sf::RectangleShape boundingRectangle;
    sf::Text healthText;
    sf::Font font;

    sf::Texture texture;
    sf::Vector2i size;
};

