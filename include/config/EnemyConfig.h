#include "SFML/Graphics.hpp"
#pragma once

struct EnemyConfig {
    std::string texturePath;
    sf::Vector2f position;
    sf::Vector2f shootingSize;
    sf::Vector2f detectionSize;
    sf::Vector2f bulletSize;
    float scale;
    int health;
    int damage;
    sf::Color bulletColor;
    float bulletSpeed;
};


