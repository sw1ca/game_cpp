#include <iostream>
#include "../../include/items/StrengthElixir.h"

StrengthElixir::StrengthElixir() : Elixir(STRENGTH_AMOUNT){}

void StrengthElixir::load() {
    if (!texture.loadFromFile("assets/images/strength_pack.png")) {
        std::cerr << "Failed to load health pack texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(3.f, 3.f);
}