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
                sf::Vector2f(2080, 1295),
                sf::Vector2f(64.f, 64.f),
                sf::Vector2f(600.f, 600.f),
                sf::Vector2f(20.f, 20.f),
                2.f,
                300,
                30,
                sf::Color::Blue,
                0.2f
        };
    }
};
