#include "HealthPack.h"

HealthPack::HealthPack() {
    active = true;
}
void HealthPack::Load() {
    if (!texture.loadFromFile("assets/images/health_pack.png")) {
        std::cerr << "Failed to load health pack texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
}
void HealthPack::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
}
void HealthPack::Initialize(sf::Vector2f position) {
    sprite.setPosition(position);
}
void HealthPack::Draw(sf::RenderWindow& window) const {
    if(active) {
        window.draw(sprite);
    }
}
bool HealthPack::isActive() const {
    return active;
}
void HealthPack::setActive(bool state) {
    active = state;
}
sf::FloatRect HealthPack::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}