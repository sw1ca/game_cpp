#include <iostream>
#include "../../include/core/Math.h"
#include "../../include/entities/Enemy.h"
#include "../../include/entities/Player.h"

int Enemy::nextId = 0;
Enemy::Enemy(Player& player, const EnemyConfig& config) :
    player(&player),
    config(config),
    health(config.health),
    maxFireRate(250),
    fireRateTimer(0),
    damage(config.damage),
    id(nextId++){}

Enemy::~Enemy() {}

void Enemy::changeHealth(int hp) {
    health += hp;
    healthText.setString(std::to_string(health));
}

void Enemy::initialize() {
    if (!texture.loadFromFile(config.texturePath)) {
        std::cout << "Failed to load texture: " << config.texturePath << std::endl;
        return;
    }

    sprite.setTexture(texture);
    sprite.setPosition(config.position);
    sprite.setScale(config.scale, config.scale);

    boundingRectangle.setSize(config.shootingSize);
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Blue);
    boundingRectangle.setOutlineThickness(1);

    detectionRectangle.setSize(config.detectionSize);
    detectionRectangle.setFillColor(sf::Color::Transparent);
    detectionRectangle.setOutlineColor(sf::Color::Red);
    detectionRectangle.setOutlineThickness(1);
}

void Enemy::load() {
    if(font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "Arial.ttf font has been loaded successfully" << std::endl;
        healthText.setFont(font);
        healthText.setCharacterSize(15);
        healthText.setString(std::to_string(health));
    }else{
        std::cout << "Failed to load Arial.ttf font" << std::endl;
    }
}

void Enemy::update(float deltaTime) {
    if(health > 0) {
        boundingRectangle.setPosition(sprite.getPosition());
        float textWidth = healthText.getLocalBounds().width;
        float textHeight = healthText.getLocalBounds().height;
        float spriteWidth = sprite.getGlobalBounds().width;
        healthText.setPosition(
                sprite.getPosition().x + (spriteWidth / 2.f) - (textWidth / 2.f),
                sprite.getPosition().y - textHeight - 5.f
                );

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

void Enemy::draw(sf::RenderWindow &window) {
    if(health > 0) {
        window.draw(sprite);
        //window.draw(boundingRectangle);
        //window.draw(detectionRectangle);
        window.draw(healthText);

        for (size_t i = 0; i < bullets.size(); ++i) {
            bullets[i].draw(window);
        }
    }
}

bool Enemy::checkPlayerDetectionCollision(const sf::RectangleShape &playerShape) {
    return detectionRectangle.getGlobalBounds().intersects(playerShape.getGlobalBounds());
}

void Enemy::shootingPlayer(float deltaTime) {
    sf::Vector2f playerPosition = player->getPosition();
    sf::RectangleShape playerShape = player->getBoundingRectanglePosition();
    if (checkPlayerDetectionCollision(playerShape) && fireRateTimer >= maxFireRate) {
        bullets.push_back(Bullet());
        int i = bullets.size() - 1;
        bullets[i].initialize(sprite.getPosition(), const_cast<sf::Vector2f &>(playerPosition), config.bulletSpeed);
        bullets[i].setBulletSize(config.bulletSize.x / 2.0f);
        bullets[i].setBulletColor(config.bulletColor);
        fireRateTimer = 0;
    }

    for (size_t i = 0; i < bullets.size(); i++) {
        bullets[i].update(deltaTime);

        if (player->health > 0) {
            if (Math::didRectCollide(bullets[i].getGlobalBounds(), playerShape.getGlobalBounds())) {
                player->changeHealth(-damage);
                bullets.erase(bullets.begin() + i); // deleting bullets
            }
        }
    }
}