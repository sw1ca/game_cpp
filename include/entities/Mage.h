#include "Enemy.h"
#include "SFML/Graphics/RenderWindow.hpp"
#pragma once

class Mage : public Enemy {
public:
    Mage(Player &player) : Enemy(player, createConfig()) {
        sprite.setTextureRect(sf::IntRect(0, 0, 128, 90));
    }
private:
    static EnemyConfig createConfig() {
        return {
                "assets/images/Mage.png",
                sf::Vector2f(3250, 900),
                sf::Vector2f(64.f, 64.f),
                sf::Vector2f(600.f, 600.f),
                sf::Vector2f(20.f, 20.f),
                1.f,
                200,
                30,
                sf::Color::Red,
                0.2f
        };
    }
};