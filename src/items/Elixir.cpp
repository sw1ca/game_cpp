#include "../../include/items/Elixir.h"

int Elixir::nextId = 0;
Elixir::Elixir(float amount) : active(true), effectAmount(amount), id(nextId++){}

void Elixir::initialize(sf::Vector2f position) {
    sprite.setPosition(position);
}
void Elixir::draw(sf::RenderWindow& window) const {
    if(active) {
        window.draw(sprite);
    }
}
void Elixir::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
}
bool Elixir::isActive() const {
    return active;
}
void Elixir::setActive(bool state) {
    active = state;
}
sf::FloatRect Elixir::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
float Elixir::getEffectAmount() const {
    return effectAmount;
}
int Elixir::getId() const {
    return id;
}