#pragma once

#include <vector>
#include <memory>
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../items/Elixir.h"
#include "SFML/Graphics.hpp"

class GameStateManager {
public:
    static bool saveGame(const Player& player, const std::vector<Enemy*>& enemies, const std::vector<std::unique_ptr<Elixir>>& elixirs);
    static bool loadGame(Player& player, std::vector<Enemy*>& enemies, std::vector<std::unique_ptr<Elixir>>& elixirs);
    static void handleInput(Player& player, std::vector<Enemy*>& enemies, std::vector<std::unique_ptr<Elixir>>& elixirs);

private:
    static std::string getSavePath();
    static bool saveKeyPressed;
    static bool loadKeyPressed;
};

