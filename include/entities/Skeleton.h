#include "Enemy.h"
#pragma once

class Skeleton : public Enemy {
public:
    Skeleton(Player &player) : Enemy(player, createConfig()) {
        sprite.setTextureRect(sf::IntRect(0, 2 * 64, 64, 64));
    }

private:
    static EnemyConfig createConfig() {
        return {
                "assets/images/spritesheet.png",
                sf::Vector2f(275.f, 400.f),
                sf::Vector2f(64.f, 64.f),
                sf::Vector2f(600.f, 600.f),
                sf::Vector2f(10.f, 10.f),
                0.8f,
                50,
                10,
                sf::Color::White,
                0.2f
        };
    }
};

