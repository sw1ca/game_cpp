#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Tile.h"
#include "Player.h"
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

    std::map<int, std::vector<int>> mapSections; // store map data for sections
    int currentSection;

    void LoadTileset(const char* tilesetPath);
    void LoadMapData(const char* mapPath, int section);
    std::string LoadFileToString(const char* filePath);
    void ParseCSVData(const std::string& csvData, int section);

public:
    Map();
    ~Map();

    void Initialize();
    void Load();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    bool IsBlocked(int x, int y);
    void MovePlayer(Player& player, sf::Vector2f direction);
    void LoadNextSection();
    void LoadSection(int section);
};