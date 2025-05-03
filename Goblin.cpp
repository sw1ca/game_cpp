#include "Goblin.h"
#include "Player.h"
#include <cmath>

Goblin::Goblin(Player& player) : Enemy(player, createConfig()) {
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    movementSpeed = 0.1f;
    attackCooldown = 1000.f;
    attackTimer = 0.0f;
    attackRange = 50.0f;
}
void Goblin::Update(float deltaTime) {
    if(health > 0) {
        boundingRectangle.setPosition(sprite.getPosition());

        float textWidth = healthText.getLocalBounds().width;
        float textHeight = healthText.getLocalBounds().height;
        float spriteWidth = sprite.getGlobalBounds().width;
        healthText.setPosition(
            sprite.getPosition().x + (spriteWidth / 2.f) - (textWidth / 2.f),
            sprite.getPosition().y - textHeight - 5.f
        );
        sf::Vector2f boundingCenter = sprite.getPosition() + (boundingRectangle.getSize() / 2.0f);
        detectionRectangle.setOrigin(detectionRectangle.getSize() / 2.0f);
        detectionRectangle.setPosition(boundingCenter);

        sf::RectangleShape playerShape = player -> getBoundingRectanglePosition();
        if (CheckPlayerDetectionCollision(playerShape)) {
            followPlayer(deltaTime);
            attackPlayer();
        }
        attackTimer += deltaTime;
    }
}
void Goblin::followPlayer(float deltaTime) {
    sf::Vector2f direction = player->getPosition() - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if(length != 0) {
        direction /= length; // Normalize the direction vector
        sprite.move(direction * movementSpeed * deltaTime);
    }
}
void Goblin::attackPlayer() {
    sf::Vector2f direction = player->getPosition() - sprite.getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if(distance <= attackRange && attackTimer >= attackCooldown) {
        player->ChangeHealth(-damage);
        attackTimer = 0.0f;
    }
}