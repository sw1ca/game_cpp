#include "HealthPack.h"

HealthPack::HealthPack() : Elixir(HEAL_AMOUNT) {}

void HealthPack::Load() {
    if (!texture.loadFromFile("assets/images/health_pack.png")) {
        std::cerr << "Failed to load health pack texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
}