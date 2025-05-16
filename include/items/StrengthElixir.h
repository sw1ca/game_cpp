#pragma once

#include "Elixir.h"
#include "SFML/Graphics.hpp"

class StrengthElixir : public Elixir {
public:
    StrengthElixir();
    bool isStrengthElixir() const override { return true; }
    void load() override;

private:
    static constexpr int STRENGTH_AMOUNT = 5;
};
