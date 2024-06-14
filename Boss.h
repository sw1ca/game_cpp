#pragma once
#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss();
    ~Boss();

    void Initialize() override;
    void Load() override;
    void Update(float deltaTime) override;
    void Draw(sf::RenderWindow& window) override;
};


