#include "Enemy.h"
#include "SFML/Graphics.hpp"
#pragma once

class Nocturne : public Enemy {
public:
    Nocturne(Player &player) : Enemy(player, createConfig()) {
        sprite.setTextureRect(sf::IntRect(224, 0, 93, 125));
    }
private:
    static EnemyConfig createConfig() {
        return {
                "assets/images/Witch.png",
                sf::Vector2f(3210, 1900),
                sf::Vector2f(64.f, 64.f),
                sf::Vector2f(600.f, 600.f),
                sf::Vector2f(20.f, 20.f),
                1.5f,
                500,
                30,
                sf::Color::Green,
                0.2f
        };
    }
};

