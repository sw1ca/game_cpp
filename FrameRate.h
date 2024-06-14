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

    void Initialize();
    void Load();
    void Update(double deltaTime);
    void Draw(sf::RenderWindow& window);
};

