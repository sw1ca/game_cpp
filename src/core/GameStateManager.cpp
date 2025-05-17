#include "../../include/core/GameStateManager.h"
#include <fstream>
#include <cstdlib>
#include <filesystem>

bool GameStateManager::saveKeyPressed = false;
bool GameStateManager::loadKeyPressed = false;

std::string GameStateManager::getSavePath() {
    const char* userProfile = std::getenv("USERPROFILE");
    if (userProfile == nullptr) {
        return "save_game.dat";
    }
    return "C:\\Users\\rswie\\OneDrive\\Pulpit\\save_game.dat";
}
bool GameStateManager::saveGame(const Player& player, const std::vector<Enemy*>& enemies, const std::vector<std::unique_ptr<Elixir>> &elixirs) {
    std::string savePath = getSavePath();
    std::filesystem::path dirPath = std::filesystem::path(savePath).parent_path();
    std::filesystem::create_directories(dirPath);

    std::ofstream saveFile(getSavePath(), std::ios::binary);
    if (!saveFile) {
        return false;
    }

    // Save player data
    int health = player.getHealth();
    sf::Vector2f playerPosition = player.getPosition();
    saveFile.write(reinterpret_cast<const char*>(&health), sizeof(health));
    saveFile.write(reinterpret_cast<const char*>(&playerPosition), sizeof(playerPosition));

    // Save enemies data
    size_t totalEnemies = enemies.size();
    saveFile.write(reinterpret_cast<const char*>(&totalEnemies), sizeof(totalEnemies));

    for (const auto& enemy : enemies) {
        int enemyId = enemy->getId();
        float enemyHealth = enemy->health;
        bool isDead = enemy->isDead();
        sf::Vector2f enemyPosition = enemy->getPosition();

        saveFile.write(reinterpret_cast<const char*>(&enemyId), sizeof(enemyId));
        saveFile.write(reinterpret_cast<const char*>(&enemyHealth), sizeof(enemyHealth));
        saveFile.write(reinterpret_cast<const char*>(&isDead), sizeof(isDead));
        saveFile.write(reinterpret_cast<const char*>(&enemyPosition), sizeof(enemyPosition));
    }

    // Save elixirs data
    size_t totalElixirs = elixirs.size();
    saveFile.write(reinterpret_cast<const char*>(&totalElixirs), sizeof(totalElixirs));

    for (const auto& elixir : elixirs) {
        int elixirId = elixir->getId();
        float effectAmount = elixir->getEffectAmount();
        sf::Vector2f elixirPosition = elixir->getPosition();
        bool isHealthElixir = elixir->isHealthElixir();
        bool isStrengthElixir = elixir->isStrengthElixir();
        bool isActive = elixir->isActive();

        saveFile.write(reinterpret_cast<const char*>(&elixirId), sizeof(elixirId));
        saveFile.write(reinterpret_cast<const char*>(&effectAmount), sizeof(effectAmount));
        saveFile.write(reinterpret_cast<const char*>(&elixirPosition), sizeof(elixirPosition));
        saveFile.write(reinterpret_cast<const char*>(&isHealthElixir), sizeof(isHealthElixir));
        saveFile.write(reinterpret_cast<const char*>(&isStrengthElixir), sizeof(isStrengthElixir));
        saveFile.write(reinterpret_cast<const char*>(&isActive), sizeof(isActive));
    }
    return true;
}
bool GameStateManager::loadGame(Player& player, std::vector<Enemy*>& enemies, std::vector<std::unique_ptr<Elixir>>& elixirs) {
    std::ifstream loadFile(getSavePath(), std::ios::binary);
    if (!loadFile.is_open()) {
        std::cout << "Could not open save file" << std::endl;
        return false;
    }

    // Load player data
    int health;
    sf::Vector2f playerPosition;
    if (!loadFile.read(reinterpret_cast<char*>(&health), sizeof(health)) ||
        !loadFile.read(reinterpret_cast<char*>(&playerPosition), sizeof(playerPosition))) {
        std::cout << "Failed to read player data" << std::endl;
        return false;
    }
    player.setHealth(health);
    player.setPosition(playerPosition);

    // Load enemies data
    size_t enemyCount;
    if (!loadFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) {
        std::cout << "Failed to read enemy count" << std::endl;
        return false;
    }

    // Update existing enemies
    for (size_t i = 0; i < enemyCount && i < enemies.size(); ++i) {
        int enemyId;
        float enemyHealth;
        bool isDead;
        sf::Vector2f enemyPosition;
        if (!loadFile.read(reinterpret_cast<char*>(&enemyId), sizeof(enemyId)) ||
            !loadFile.read(reinterpret_cast<char*>(&enemyHealth), sizeof(enemyHealth)) ||
            !loadFile.read(reinterpret_cast<char*>(&isDead), sizeof(isDead)) ||
            !loadFile.read(reinterpret_cast<char*>(&enemyPosition), sizeof(enemyPosition))) {
            std::cout << "Failed to read enemy data" << std::endl;
            return false;
        }
        auto it = std::find_if(enemies.begin(), enemies.end(),
            [enemyId](const Enemy* enemy){
                return enemy->getId() == enemyId;
        });

        if (it != enemies.end()) {
            (*it)->health = enemyHealth;
            if (isDead) {
                (*it)->die();
            }
            (*it)->setPosition(enemyPosition);
        }
    }
    // Load elixirs data

    size_t totalElixirs;
    if (!loadFile.read(reinterpret_cast<char*>(&totalElixirs), sizeof(totalElixirs))) {
        std::cout << "Failed to read elixir count" << std::endl;
        return false;
    }

    for (size_t i = 0; i < totalElixirs; ++i) {
        int elixirId;
        float effectAmount;
        sf::Vector2f elixirPosition;
        bool isHealthElixir;
        bool isStrengthElixir;
        bool isActive;

    if (!loadFile.read(reinterpret_cast<char*>(&elixirId), sizeof(elixirId)) ||
        !loadFile.read(reinterpret_cast<char*>(&effectAmount), sizeof(effectAmount)) ||
        !loadFile.read(reinterpret_cast<char*>(&elixirPosition), sizeof(elixirPosition)) ||
        !loadFile.read(reinterpret_cast<char*>(&isHealthElixir), sizeof(isHealthElixir)) ||
        !loadFile.read(reinterpret_cast<char*>(&isStrengthElixir), sizeof(isStrengthElixir)) ||
        !loadFile.read(reinterpret_cast<char*>(&isActive), sizeof(isActive))) {
        std::cout << "Failed to read elixir data" << std::endl;
        return false;
    }

    auto it = std::find_if(elixirs.begin(), elixirs.end(),
   [elixirId](const std::unique_ptr<Elixir>& elixir) {
           return elixir->getId() == elixirId;
    });

    if (it != elixirs.end()) {
        (*it)->setPosition(elixirPosition);
        (*it)->setActive(isActive);
        (*it)->setEffectAmount(effectAmount);
    }
}

    loadFile.close();
    std::cout << "Game loaded successfully" << std::endl;
    return true;
}
void GameStateManager::handleInput(Player& player, std::vector<Enemy*>& enemies, std::vector<std::unique_ptr<Elixir>>& elixirs) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
        if(!saveKeyPressed) {
            saveKeyPressed = true;
            if(saveGame(player, enemies, elixirs)) {
                std::cout << "Game saved successfully!\n" << std::endl;
            } else {
                std::cout << "Failed to save game.\n" << std::endl;
            }
        }
    } else {
        saveKeyPressed = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
        if(!loadKeyPressed) {
            loadKeyPressed = true;
            if(loadGame(player, enemies, elixirs)) {
                std::cout << "Game loaded successfully!\n" << std::endl;
            } else {
                std::cout << "Failed to load game.\n" << std::endl;
            }
        }
    } else {
        loadKeyPressed = false;
    }
}