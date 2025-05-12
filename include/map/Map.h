#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Tile.h"
#include "../entities/Player.h"
#include <vector>
#include <string>

class Map {
private:
    sf::Texture tileSheetTexture;
    Tile* tiles;

    int totalTiles;
    int tileWidth;
    int tileHeight;

    int totalTilesX;
    int totalTilesY;

    int mapWidth;
    int mapHeight;
    std::vector<int> mapData;
    std::vector<sf::Sprite> mapSprites;

    void loadTileset(const char* tilesetPath);
    void loadMapData(const char* mapPath);
    std::string loadFileToString(const char* filePath);
    void parseCSVData(const std::string& csvData);

public:
    Map();
    ~Map();

    void initialize();
    void load();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isBlocked(int x, int y);
    void movePlayer(Player& player, sf::Vector2f direction);
    void loadSection(int section);
    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }
    int getTileWidth() const { return tileWidth; }
    int getTileHeight() const { return tileHeight; }
};