/*
#include "GameStateManager.h"
#include <iostream>

void GameStateManager::SaveGame(Player &player, std::vector<Enemy *> &enemies) {
    std::ofstream saveFile("savegame.txt");
    if(saveFile.is_open()) {
        saveFile << player.health << "\n";
        sf::Vector2f playerPosition = player.getPosition();
        saveFile << playerPosition.x << " " << playerPosition.y << "\n";

        for(Enemy* enemy : enemies) {
            saveFile << enemy -> health << "\n";
            sf::Vector2f enemyPosition = enemy -> sprite.getPosition();
            saveFile << enemyPosition.x << " " << enemyPosition.y << "\n";
        }
        saveFile.close();
        std::cout << "Game saved successfully!" << std::endl;
    }else{
        std::cout << "Unable to open save file!" << std::endl;
    }
}
void GameStateManager::LoadGame(Player &player, std::vector<Enemy *> &enemies) {
    std::ifstream loadFile("savegame.txt");
    if (loadFile.is_open()) {
        loadFile >> player.health;
        float playerX, playerY;
        loadFile >> playerX >> playerY;
        player.setPosition(sf::Vector2f(playerX, playerY));

        for (Enemy *enemy: enemies) {
            loadFile >> enemy->health;
            float enemyX, enemyY;
            loadFile >> enemyX >> enemyY;
            enemy->sprite.setPosition(sf::Vector2f(enemyX, enemyY));
        }
        loadFile.close();
        std::cout << "Game loaded successfully!" << std::endl;
    } else {
        std::cout << "Unable to open load file!" << std::endl;
    }
}
*/
