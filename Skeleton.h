#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

class Skeleton {
private:
    sf::Texture skeletonTexture;

    sf::Text healthText;
    sf::Font font;

public:
    sf::Sprite skeletonSprite;

    sf::RectangleShape boundingRectangle;
    sf::Vector2i size;

    int health;
public:
    Skeleton();
    ~Skeleton();

    void ChangeHealth(int hp);

    void Initialize();
    void Load();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
};

