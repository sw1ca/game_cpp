#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Bullet {
private:
    sf::CircleShape circleShape;
    sf::Vector2f direction;
    float speed;
public:
    Bullet();
    ~Bullet();

    void Initialize(const sf::Vector2f& position, sf::Vector2f& target, float speed);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    void setBulletSize(const float radius);
    sf::FloatRect GetGlobalBounds() const { return circleShape.getGlobalBounds(); }
    void setBulletColor(const sf::Color& color);
};

