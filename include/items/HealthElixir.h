#include <iostream>
#include "SFML/Graphics.hpp"
#include "Elixir.h"
#pragma once

class HealthElixir : public Elixir {
public:
    HealthElixir();
    bool isHealthElixir() const override { return true; }
    void load() override;
private:
    static constexpr float HEAL_AMOUNT = 50.0f;
};