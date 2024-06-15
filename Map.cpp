#include <iostream>
#include <fstream>
#include <sstream>
#include "Map.h"

Map::Map() : tileWidth(16), tileHeight(16), totalTilesX(0), totalTilesY(0), mapWidth(0), mapHeight(0) {}

Map::~Map() {
    delete[] tiles;
}

void Map::Initialize() {}

void Map::LoadTileset(const char* tilesetPath) {
    if (tileSheetTexture.loadFromFile(tilesetPath)) { // 224x240
        std::cout << "Map sheet images Loaded!" << std::endl;

        totalTilesX = tileSheetTexture.getSize().x / tileWidth;
        totalTilesY = tileSheetTexture.getSize().y / tileHeight;

        totalTiles = totalTilesX * totalTilesY;
        tiles = new Tile[totalTiles];

        for (size_t y = 0; y < totalTilesY; y++) {
            for (size_t x = 0; x < totalTilesX; x++) {
                int i = x + y * totalTilesX;
                tiles[i].id = i;
                tiles[i].texture = &tileSheetTexture;
                tiles[i].rect = sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
            }
        }
    } else {
        std::cout << "Map sheet images failed to load!" << std::endl;
    }
}

std::string Map::LoadFileToString(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Map::ParseCSVData(const std::string& csvData) {
    std::stringstream ss(csvData);
    std::string item;
    while (std::getline(ss, item, ',')) {
        int tileID = std::stoi(item) - 1; // TMX index starts at 1, adjust to 0
        mapData.push_back(tileID >= 0 ? tileID : -1); // Ensure valid tile ID or set to -1
    }

    mapSprites.resize(mapWidth * mapHeight);
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int i = x + y * mapWidth;
            int tileId = mapData[i];

            if (tileId >= 0 && tileId < totalTiles) {
                mapSprites[i].setTexture(*tiles[tileId].texture);
                mapSprites[i].setTextureRect(tiles[tileId].rect);
                mapSprites[i].setPosition(sf::Vector2f(x * tileWidth, y * tileHeight));
            }
        }
    }
}

void Map::LoadMapData(const char* mapPath) {
    std::string fileContent = LoadFileToString(mapPath);
    if (fileContent.empty()) return;

    size_t mapStart = fileContent.find("<map");
    size_t mapEnd = fileContent.find("</map>") + 6;

    std::string mapDataContent = fileContent.substr(mapStart, mapEnd - mapStart);

    size_t widthPos = mapDataContent.find("width=\"") + 7;
    size_t widthEnd = mapDataContent.find("\"", widthPos);
    mapWidth = std::stoi(mapDataContent.substr(widthPos, widthEnd - widthPos));

    size_t heightPos = mapDataContent.find("height=\"") + 8;
    size_t heightEnd = mapDataContent.find("\"", heightPos);
    mapHeight = std::stoi(mapDataContent.substr(heightPos, heightEnd - heightPos));

    size_t dataPos = mapDataContent.find("<data encoding=\"csv\">") + 21;
    size_t dataEnd = mapDataContent.find("</data>");
    std::string csvData = mapDataContent.substr(dataPos, dataEnd - dataPos);

    ParseCSVData(csvData);
}

void Map::Load() {
    LoadTileset("assets/Map/Tilesheet.png");
    LoadMapData("assets/Map/map.tmx");
}
void Map::Update(float deltaTime) {}

void Map::Draw(sf::RenderWindow &window) {
    for (const auto& sprite : mapSprites) {
        window.draw(sprite);
    }
}
