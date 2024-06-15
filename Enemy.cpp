#include <iostream>
#include "Math.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(Player& player) : health(100), player(&player), maxFireRate(250), fireRateTimer(0) {}
Enemy::~Enemy() {}

void Enemy::ChangeHealth(int hp) {
    health += hp;
    healthText.setString(std::to_string(health));
}

void Enemy::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Blue);
    boundingRectangle.setOutlineThickness(1);

    detectionRectangle.setFillColor(sf::Color::Transparent);
    detectionRectangle.setOutlineColor(sf::Color::Red);
    detectionRectangle.setOutlineThickness(1);
}

void Enemy::Load() {
    if(font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "Arial.ttf font has been loaded successfully" << std::endl;
        healthText.setFont(font);
        healthText.setString(std::to_string(health));
    }else{
        std::cout << "Failed to load Arial.ttf font" << std::endl;
    }
}

void Enemy::Update(float deltaTime) {
    if(health > 0) {
        boundingRectangle.setPosition(sprite.getPosition());
        healthText.setPosition(sprite.getPosition());

        // Calculate the center of the boundingRectangle
        sf::Vector2f boundingCenter = sprite.getPosition() + (boundingRectangle.getSize() / 2.0f);

        // Set the origin of the detectionRectangle to its center
        detectionRectangle.setOrigin(detectionRectangle.getSize() / 2.0f);

        // Position the detectionRectangle at the center of the boundingRectangle
        detectionRectangle.setPosition(boundingCenter);

        fireRateTimer += deltaTime;
        shootingPlayer(deltaTime);
    }
}

void Enemy::Draw(sf::RenderWindow &window) {
    if(health > 0) {
        window.draw(sprite);
        window.draw(boundingRectangle);
        window.draw(detectionRectangle);
        window.draw(healthText);

        for (size_t i = 0; i < bullets.size(); ++i) {
            bullets[i].Draw(window);
        }
    }
}

bool Enemy::CheckPlayerDetectionCollision(const sf::RectangleShape &playerShape) {
    return detectionRectangle.getGlobalBounds().intersects(playerShape.getGlobalBounds());
}

void Enemy::shootingPlayer(float deltaTime) {
    sf::Vector2f playerPosition = player->getPosition();
    sf::RectangleShape playerShape = player->getBoundingRectanglePosition();
    std::cout << "fireRateTimer: "<< fireRateTimer << std::endl;
    std::cout << "maxFireRate: "<< maxFireRate << std::endl;
    if(CheckPlayerDetectionCollision(playerShape) && fireRateTimer >= maxFireRate) {
        bullets.push_back(Bullet());
        int i = bullets.size() - 1;
        bullets[i].Initialize(sprite.getPosition(), const_cast<sf::Vector2f &>(playerPosition), 0.2f);
        fireRateTimer = 0;
    }

    for(size_t i = 0; i < bullets.size(); i++) {
        bullets[i].Update(deltaTime);

        if (Math::didRectCollide(bullets[i].GetGlobalBounds(), playerShape.getGlobalBounds())) {
            bullets.erase(bullets.begin() + i); // deleting bullets
        }
    }
}