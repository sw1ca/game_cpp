#pragma once

#include "../../include/items/StrengthElixir.h"
#include "../../include/items/HealthElixir.h"
#include "SFML/System/Vector2.hpp"
#include <vector>
#include <memory>

class ElixirConfig {
public:
    template<typename T>
    static void createElixirs(std::vector<std::unique_ptr<Elixir>>& elixirs, const std::vector<sf::Vector2f>& positions) {
        for (const auto& position : positions) {
            auto elixir = std::make_unique<T>();
            elixir->load();
            elixir->initialize(position);
            elixirs.push_back(std::move(elixir));
        }
    }
};