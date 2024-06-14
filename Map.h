#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Tile.h"

class Map {
private:
    sf::Texture tileSheetTexture;
    Tile* tiles;

    int totalTiles;

    int tileWidth;
    int tileHeight;

    int totalTilesX;
    int totalTilesY;

    int mapNumbers[6] = {
            1, 1, 1,
            17, 31, 165
    };

    sf::Sprite mapSprites[6];
public:
    Map();
    ~Map();

    void Initialize();
    void Load();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
};
