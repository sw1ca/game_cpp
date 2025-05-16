#pragma once
#include "SFML/Graphics.hpp"

class Elixir {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    bool active;
    float effectAmount;
    const int id;
    static int nextId;

public:
    Elixir(float amount);
    virtual ~Elixir() = default;

    virtual void initialize(sf::Vector2f position);
    virtual void load() = 0;
    virtual void draw(sf::RenderWindow& window) const;
    virtual bool isHealthElixir() const { return false; }
    virtual bool isStrengthElixir() const { return false; }
    virtual sf::Vector2f getPosition() const { return sprite.getPosition(); }
    virtual void setEffectAmount(float amount) { effectAmount = amount; }

    void setPosition(sf::Vector2f position);
    bool isActive() const;
    void setActive(bool state);
    sf::FloatRect getGlobalBounds() const;
    float getEffectAmount() const;
    int getId() const;
};

