#include <iostream>
#include <fstream>
#include <sstream>
#include "Map.h"

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

        ParseCSVData(csvData, section);
}

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
                // Mark specific tiles as blocked
                if(i == 41 || i == 55 || i == 54 || i == 53 || i == 52 || i == 51 ||
                   i == 50 || i == 49 || i == 48 || i == 47 || i == 46 || i == 60 ||
                   i == 61 || i == 62 || i == 63 || i == 64 || i == 65 || i == 66 || i == 67 ||
                   i == 68 || i == 69 || i == 70 || i == 82 || i == 83 || i == 84 || i == 118 ||
                   i == 119 || i == 133 || i == 134 || i == 127 || i == 128 || i == 129 || i == 130 ||
                   i == 141 || i == 142 || i == 143 || i == 144 || i == 155 || i == 156 ||
                   i == 157 || i == 158 || i == 168 || i == 169 || i == 170 || i == 171 || i == 172 ||
                   i == 173 || i == 173 || i == 174 || i == 175 || i == 176 || i == 177 || i == 178 ||
                   i == 182 || i == 183 || i == 184 || i == 185 || i == 186 || i == 187 || i == 188 ||
                   i == 189 || i == 190 || i == 191 || i == 192 || i == 196 || i == 197 || i == 198 ||
                   i == 199 || i == 151 || i == 152 || i == 153 || i == 165 || i == 166 || i == 167 ||
                   i == 179 || i == 180 || i == 181) {
                    tiles[i].blocked = true;
                }
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

void Map::ParseCSVData(const std::string& csvData, int section) {
    std::stringstream ss(csvData);
    std::string item;
    std::vector<int> sectionData;
    while (std::getline(ss, item, ',')) {
        int tileID = std::stoi(item) - 1; // TMX index starts at 1, adjust to 0
        sectionData.push_back(tileID >= 0 ? tileID : -1); // Ensure valid tile ID or set to -1
    }

    mapSections[section] = sectionData;

    if(section == 0) {
        mapData = sectionData;
    }else {
        mapData.insert(mapData.end(), sectionData.begin(), sectionData.end());
    }
    mapSprites.resize(mapWidth * mapHeight * (currentSection + 1));
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int i = x + y * mapWidth + section * mapWidth * mapHeight;
            int tileId = mapData[x + y * mapWidth + section * mapWidth * mapHeight];

            if (tileId >= 0 && tileId < totalTiles) {
                mapSprites[i].setTexture(*tiles[tileId].texture);
                mapSprites[i].setTextureRect(tiles[tileId].rect);
                mapSprites[i].setPosition(sf::Vector2f((x + section * mapWidth) * tileWidth, y * tileHeight));
            }
        }
    }
}
void Map::LoadNextSection() {
    currentSection++;
    mapSprites.clear();
    LoadSection(currentSection);
}

void Map::LoadMapData(const char* mapPath, int section) {
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

    ParseCSVData(csvData, section);
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
        LoadNextSection();
        /*newPosition.x = rightBorder - player.getSize().x;*/
        newPosition.x = 0;
    }
    if(!IsBlocked(newPosition.x, newPosition.y)) {
        player.setPosition(newPosition);
    }
}
