#include "SFML/Graphics.hpp"

struct EnemyConfig {
    std::string texturePath;
    sf::Vector2f position;
    sf::Vector2f shootingSize;
    sf::Vector2f detectionSize;
    sf::Vector2f bulletSize;
    float scale;
    int health;
    int bulletDamage;
    sf::Color bulletColor;
};


