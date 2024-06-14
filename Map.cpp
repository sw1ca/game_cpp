#include <iostream>
#include "Map.h"

Map::Map() : tileWidth(16), tileHeight(16), totalTilesX(0), totalTilesY(0) {
}
Map::~Map() {

}
void Map::Initialize() {

}

void Map::Load() {
    if(tileSheetTexture.loadFromFile("assets/Map/Tilesheet.png")){ // 224x240

        std::cout << "Map sheet images Loaded!" << std::endl;

        totalTilesX = tileSheetTexture.getSize().x / tileWidth;
        totalTilesY = tileSheetTexture.getSize().y / tileHeight;

        std::cout << totalTilesX << std::endl; // 14
        std::cout << totalTilesY << std::endl; // 15

        totalTiles = totalTilesX * totalTilesY;

        tiles = new Tile[totalTiles];

        for(size_t y = 0; y < totalTilesY; y++) {
            for (size_t x = 0; x < totalTilesX; x++) {
                int i = x + y * totalTilesX;

                tiles[i].id = i;
                tiles[i].texture = &tileSheetTexture;
                tiles[i].rect = sf::IntRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));

                //tiles[i].sprite.setTexture(tileSheetTexture);
                //tiles[i].sprite.setScale(sf::Vector2f(2.5, 2.5));
                //tiles[i].sprite.setPosition(sf::Vector2f(x * tileWidth * 2.5, 50 + y * tileWidth * 2.5));
            }
        }
    } else {
        std::cout << "Map sheet images failed to loaded!" << std::endl;
    }

    for (size_t y = 0; y < 2; y++) {
        for(size_t x = 0; x < 3; x++) {
            int i = x + y * 3;

            int index = mapNumbers[i];

            mapSprites[i].setTexture(*tiles[index].texture);
            mapSprites[i].setTextureRect(tiles[index].rect);
            mapSprites[i].setScale(sf::Vector2f(2.5, 2.5));
            mapSprites[i].setPosition(sf::Vector2f(x * 16, y * 16));
        }
    }
}

void Map::Update(float deltaTime) {

}

void Map::Draw(sf::RenderWindow &window) {
    for (size_t i = 0; i < 6; ++i) {
        window.draw(mapSprites[i]);
    }
}
