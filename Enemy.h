#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Enemy {
public:
    sf::Sprite sprite;
    int health;

    Enemy();
    virtual ~Enemy();

    virtual void Initialize();
    virtual void Load();
    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow& window);

    void ChangeHealth(int hp);
    inline const sf::Rect<float> GetGlobalBounds() const { return sprite.getGlobalBounds(); }
    bool CheckPlayerDetectionCollision(const sf::RectangleShape& playerShape);

protected:
    sf::RectangleShape boundingRectangle;
    sf::RectangleShape detectionRectangle;
    sf::Text healthText;
    sf::Font font;

    sf::Texture texture;
    sf::Vector2i shootingSize;
    sf::Vector2i detectionSize;
};