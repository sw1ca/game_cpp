#include "Enemy.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Golem : public Enemy {
public:
    Golem(Player &player) : Enemy(player, CreateConfig()) {
        sprite.setTextureRect(sf::IntRect(0, 2 * 64, 64, 64));
    }
private:
    static EnemyConfig CreateConfig() {
        return {
                "assets/images/Golem.png",
                sf::Vector2f(2085, 1300),
                sf::Vector2f(64.f, 64.f),
                sf::Vector2f(600.f, 600.f),
                sf::Vector2f(20.f, 20.f),
                1.8f,
                500,
                50,
                sf::Color::Blue,
                0.2f
        };
    }
};
