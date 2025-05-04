#include "Enemy.h"

class Goblin : public Enemy {
public:
    Goblin(Player &player);
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
                "assets/images/goblin.png",
                sf::Vector2f(300.f, 1500.f),
                sf::Vector2f(64.f, 64.f),
                sf::Vector2f(600.f, 600.f),
                sf::Vector2f(10.f, 10.f),
                0.8f,
                50,
                25,
                sf::Color::White,
                0.0f
        };
    }
};