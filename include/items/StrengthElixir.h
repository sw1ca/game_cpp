#pragma once

#include "Elixir.h"
#include "SFML/Graphics.hpp"

class StrengthElixir : public Elixir {
public:
    StrengthElixir();
    void load() override;
    bool isStrengthElixir() const override { return true; }

private:
    static constexpr int STRENGTH_AMOUNT = 5;
};
