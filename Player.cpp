#include "Player.h"
#include "Math.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Mouse.hpp"
#include <iostream>

Player::Player() : health(200), playerSpeed(0.8f), maxfireRate(150), fireRateTimer(0) {}
Player::~Player() {}

void Player::ChangeHealth(int hp) {
    health += hp;
    healthText.setString(std::to_string(health));
}
void Player::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(64, 64);

    goUpTexture = sf::IntRect(0, 0, size.x, size.y);
    goLeftTexture = sf::IntRect(0, 1 * size.y, size.x, size.y);
    goRightTexture = sf::IntRect(0, 3 * size.y, size.x, size.y);
    goDownTexture = sf::IntRect(0, 2 * size.y, size.x, size.y);

}
void Player::Load() {
    if(font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "Arial.ttf font has been loaded successfully" << std::endl;
        healthText.setFont(font);
        healthText.setString(std::to_string(health));
    }else{
        std::cout << "Failed to load Arial.ttf font" << std::endl;
    }
    if(playerTexture.loadFromFile("assets/images/spritesheet.png")){
        std::cout << "Player Images Loaded!" << std::endl;
        playerSprite.setTexture(playerTexture);

        int XIndex = 0;
        int YIndex = 3;

        playerSprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        playerSprite.setPosition(sf::Vector2f(0, 0));

        playerSprite.scale(sf::Vector2f(1.5, 1.5));
        boundingRectangle.setSize(sf::Vector2f(size.x * playerSprite.getScale().x, size.y * playerSprite.getScale().y));
    } else {
        std::cout << "Player image failed to loaded!" << std::endl;
    }
}
void Player::Update(float deltaTime, std::vector<Enemy*>& enemies, sf::Vector2f& mousePosition) {
    if(health > 0) {
        sf::Vector2f position = playerSprite.getPosition();
        healthText.setPosition(playerSprite.getPosition());
        sf::Vector2f movement(0.f, 0.f);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= 0.75f;
            playerSprite.setTextureRect(goUpTexture);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= 0.75f;
            playerSprite.setTextureRect(goLeftTexture);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += 0.75f;
            playerSprite.setTextureRect(goDownTexture);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += 0.75f;
            playerSprite.setTextureRect(goRightTexture);
        }

        playerSprite.setPosition(position + movement * playerSpeed * deltaTime);

        boundingRectangle.setPosition(position + movement * playerSpeed * deltaTime);
        // -------------------------------------------------------------------
        fireRateTimer += deltaTime;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireRateTimer >= maxfireRate) {
            bullets.push_back(Bullet());
            int i = bullets.size() - 1;
            bullets[i].Initialize(playerSprite.getPosition(), mousePosition, 0.5f);
            fireRateTimer = 0;
        }

        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].Update(deltaTime);

            for (Enemy *enemy: enemies) {
                if (enemy->health > 0) {
                    if (Math::didRectCollide(bullets[i].GetGlobalBounds(), enemy->GetGlobalBounds())) {
                        enemy->ChangeHealth(-10);
                        bullets.erase(bullets.begin() + i); // deleting bullets
                    }
                }
            }
        }
    }
    // -------------------------------------------------------------------

}

void Player::Draw(sf::RenderWindow& window) {
    if (health > 0) {
        window.draw(playerSprite);
        window.draw(boundingRectangle);
        window.draw(healthText);

        for (size_t i = 0; i < bullets.size(); ++i) {
            bullets[i].Draw(window);
        }
    }
}

sf::Vector2f Player::getPosition() const {
    return playerSprite.getPosition();
}

sf::RectangleShape Player::getBoundingRectanglePosition() const {
    return boundingRectangle;
}