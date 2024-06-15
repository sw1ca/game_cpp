#include "Boss.h"
#include <iostream>

Boss::Boss(Player& player) : player(player) {
    health = 500;
}
Boss::~Boss() {}
void Boss::Initialize() {
    Enemy::Initialize();
    shootingSize = sf::Vector2i(64, 64);
    detectionSize = sf::Vector2i(128, 128);
}
//void Boss::setPlayer(Player& player) {
//    this -> player = player;
//}
void Boss::Load() {
    Enemy::Load();
    if(font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "Arial.ttf font has been loaded successfully" << std::endl;
        healthText.setFont(font);
        healthText.setString(std::to_string(health));
    }else{
        std::cout << "Failed to load Arial.ttf font" << std::endl;
    }
    if(texture.loadFromFile("assets/images/Boss.png")){
        std::cout << "Boss Images Loaded!" << std::endl;
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(1000, 200));

        int XIndex = 3;
        int YIndex = 0;

        sprite.setTextureRect(sf::IntRect(XIndex * shootingSize.x, YIndex * shootingSize.y, shootingSize.x, shootingSize.y));
        sprite.scale(sf::Vector2f(3, 3));

        boundingRectangle.setSize(sf::Vector2f(shootingSize.x * sprite.getScale().x, shootingSize.y * sprite.getScale().y));
        detectionRectangle.setSize(sf::Vector2f(detectionSize.x * sprite.getScale().x, detectionSize.y * sprite.getScale().y));
    } else {
        std::cout << "Boss image failed to loaded!" << std::endl;
    }
}

void Boss::Update(float deltaTime, sf::Vector2f playerPosition, const sf::RectangleShape& playerShape, std::vector<Enemy *>& enemies) {
    Enemy::Update(deltaTime, playerPosition, playerShape,enemies);
    shootingPlayer(player.getPosition());
}

void Boss::Draw(sf::RenderWindow &window) {
    Enemy::Draw(window);
}

//void Boss::shootingPlayer(const sf::Vector2f& playerPosition, const sf::RectangleShape& playerShape, float deltaTime) {
//    if (CheckPlayerDetectionCollision(boundingRectangle) && fireRateTimer >= maxFireRate) {
//        bullets.push_back(Bullet());
//        int i = bullets.size() - 1;
//        bullets[i].Initialize(sprite.getPosition(), const_cast<sf::Vector2f &>(playerPosition), 0.5f);
//        fireRateTimer = 0;
//    }
//    for (size_t i = 0; i < bullets.size(); i++) {
//        bullets[i].Update(0);
//    }
//}