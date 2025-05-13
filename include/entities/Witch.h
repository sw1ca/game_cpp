#include "Enemy.h"
#include "SFML/Graphics/RenderWindow.hpp"
#pragma once

class Witch : public Enemy {
public:
    Witch(Player &player) : Enemy(player, createConfig()) {
        sprite.setTextureRect(sf::IntRect(85, 0, 130, 128));
    }
    bool isBoss() const override { return true; }

private:
    static EnemyConfig createConfig() {
        return {
                "assets/images/Witch.png",
                sf::Vector2f(1125, 1945),
                sf::Vector2f(64.f, 64.f),
                sf::Vector2f(600.f, 600.f),
                sf::Vector2f(20.f, 20.f),
                1.5f,
                250,
                30,
                sf::Color::Yellow,
                0.2f
        };
    }
};