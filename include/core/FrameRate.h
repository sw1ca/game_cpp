#pragma once

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class FrameRate {
private:
    sf::Text frameRateText; // Sprite
    sf::Font font; // Textures

    float timer;

public:
    FrameRate();
    ~FrameRate();

    void initialize();
    void load();
    void update(double deltaTime);
    void draw(sf::RenderWindow& window);
};

