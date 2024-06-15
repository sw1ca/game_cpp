#pragma once
#include "Enemy.h"

class Skeleton : public Enemy {
public:
    Skeleton(Player &player);

    ~Skeleton();

    void Initialize() override;
    void Load() override;
    void Update(float deltaTime) override;
    void Draw(sf::RenderWindow& window) override;
};

