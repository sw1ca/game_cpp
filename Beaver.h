#include "Enemy.h"

class Beaver : public Enemy {
public:
    Beaver(Player& player);
    void Update(float deltaTime) override;
private:
    float movementSpeed;
    float attackCooldown;
    float attackTimer;
    float attackRange;
    void followPlayer(float deltaTime);
    void attackPlayer();

    static EnemyConfig createConfig() {
        return {
            "assets/images/beaverGangster.png",
            sf::Vector2f(1000.f, 1050.f),
            sf::Vector2f(64.f, 64.f),
            sf::Vector2f(600.f, 600.f),
            sf::Vector2f(10.f, 10.f),
            1.2f,
            50,
            25,
            sf::Color::White,
            0.0f
        };
    }
};

