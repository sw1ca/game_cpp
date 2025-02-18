#pragma once

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

struct Tile {
    int id = -1;

    sf::Texture* texture = nullptr;
    sf::IntRect rect;
    bool blocked;

    Tile() : id(-1), texture(nullptr), blocked(false) {}
};