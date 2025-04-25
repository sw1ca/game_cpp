#include <iostream>
#include <fstream>
#include <sstream>
#include "Map.h"
#include <unordered_set>

Map::Map() : tileWidth(16), tileHeight(16), totalTilesX(0), totalTilesY(0), mapWidth(0), mapHeight(0) {}

Map::~Map() {
    delete[] tiles;
}
void Map::Load() {
    LoadTileset("assets/Map/Tilesheet.png");
    LoadSection(0);
}
void Map::Initialize() {}
void Map::LoadSection(int section) {
        std::string sectionPath = "assets/Map/map0.tmx";
        std::string fileContent = LoadFileToString(sectionPath.c_str());
        if (fileContent.empty()) return;


        size_t mapStart = fileContent.find("<map");
        size_t mapEnd = fileContent.find("</map") + 6;

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

void Map::LoadTileset(const char* tilesetPath) {
    if (tileSheetTexture.loadFromFile(tilesetPath)) { // 224x240
        std::cout << "Map sheet images Loaded!" << std::endl;

        totalTilesX = tileSheetTexture.getSize().x / tileWidth;
        totalTilesY = tileSheetTexture.getSize().y / tileHeight;

        totalTiles = totalTilesX * totalTilesY;
        tiles = new Tile[totalTiles];

        static const std::unordered_set<int> blockedTiles = {
            41, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 60, 61, 62, 63, 64, 65, 66, 67,
            68, 69, 70, 82, 83, 84, 118, 119, 133, 134, 127, 128, 129, 130, 141, 142, 143,
            144, 155, 156, 157, 158, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178,
            182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 196, 197, 198, 199, 151,
            152, 153, 165, 166, 167, 179, 180, 181
        };

        for (size_t y = 0; y < totalTilesY; y++) {
            for (size_t x = 0; x < totalTilesX; x++) {
                int i = x + y * totalTilesX;
                tiles[i].id = i;
                tiles[i].texture = &tileSheetTexture;
                tiles[i].rect = sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
                // Mark specific tiles as blocked
                tiles[i].blocked = (blockedTiles.find(i) != blockedTiles.end());
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
    std::vector<int> sectionData;
    while (std::getline(ss, item, ',')) {
        int tileID = std::stoi(item) - 1; // TMX index starts at 1, adjust to 0
        sectionData.push_back(tileID >= 0 ? tileID : -1); // Ensure valid tile ID or set to -1
    }

    mapData = sectionData;

    mapSprites.resize(mapWidth * mapHeight);
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int i = x + y * mapWidth;
            int tileId = mapData[x + y * mapWidth];

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
void Map::Update(float deltaTime) {}

void Map::Draw(sf::RenderWindow &window) {
    for (const auto& sprite : mapSprites) {
        window.draw(sprite);
    }
}
bool Map::IsBlocked(int x, int y) {
    int tileX = x / tileWidth;
    int tileY = y / tileHeight;
    int index = tileX + tileY * mapWidth;

    if(index < 0 || index >= mapWidth * mapHeight) {
        return true;
    }

    int tileId = mapData[index];
    return tiles[tileId].blocked;
}
void Map::MovePlayer(Player &player, sf::Vector2f direction) {
    sf::Vector2f newPosition = player.getPosition() + direction;

    // Define border positions
    float leftBorder = 0.0f;
    float topBorder = 0.0f;
    float bottomBorder = mapHeight * tileHeight;
    float rightBorder = mapWidth * tileWidth;

    //Check if the new position crosses any of the borders
    if(newPosition.x < leftBorder) {
        newPosition.x = leftBorder;
    }
    if(newPosition.y < topBorder) {
        newPosition.y = topBorder;
    }
    if(newPosition.y + player.getSize().y > bottomBorder) {
        newPosition.y = bottomBorder - player.getSize().y;
    }
    if(newPosition.x + player.getSize().x > rightBorder) {
        newPosition.x = rightBorder - player.getSize().x;
    }
    if(!IsBlocked(newPosition.x, newPosition.y)) {
        player.setPosition(newPosition);
    }

}
