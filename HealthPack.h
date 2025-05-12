#include <iostream>
#include "SFML/Graphics.hpp"
#include "Elixir.h"
#pragma once

class HealthPack : public Elixir {
public:
    HealthPack();
    void Load() override;

private:
    static constexpr float HEAL_AMOUNT = 50.0f;
};