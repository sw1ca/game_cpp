#pragma once

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

struct Tile {
    int id = -1;

    sf::Texture* texture = nullptr;
    sf::IntRect rect;
};