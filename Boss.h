#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(Player &player) : Enemy(player, CreateConfig()) {
        sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    }
private:
    static EnemyConfig CreateConfig() {
        return {
                "assets/images/Boss.png",
                sf::Vector2f(1520, 705),
                sf::Vector2f(64.f, 64.f),
                sf::Vector2f(600.f, 600.f),
                sf::Vector2f(20.f, 20.f),
                2.f,
                300,
                30,
                sf::Color::Red,
                0.1f
        };
    }
};


