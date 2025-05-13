#pragma once
#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(Player &player) : Enemy(player, createConfig()) {
        sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    }
    bool isBoss() const override { return true; }

private:
    static EnemyConfig createConfig() {
        return {
                "assets/images/Boss.png",
                sf::Vector2f(1520, 705),
                sf::Vector2f(64.f, 64.f),
                sf::Vector2f(600.f, 600.f),
                sf::Vector2f(20.f, 20.f),
                2.f,
                300,
                25,
                sf::Color::Red,
                0.2f
        };
    }
};


