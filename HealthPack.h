#include <iostream>
#include "SFML/Graphics.hpp"
#pragma once

class HealthPack {
public:
    HealthPack();

    void Initialize(sf::Vector2f position);
    void Draw(sf::RenderWindow& window) const;
    void Load();
    void setPosition(sf::Vector2f position);
    bool isActive() const;
    void setActive(bool state);
    sf::FloatRect getGlobalBounds() const;
    static float getHealAmount() {
        return HEAL_AMOUNT;
    }

private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool active;
    static constexpr float HEAL_AMOUNT = 50.0f;
};
