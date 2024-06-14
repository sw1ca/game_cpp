#include "Player.h"
#include "Math.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Mouse.hpp"
#include <iostream>

Player::Player() : playerSpeed(0.8f), maxfireRate(150), fireRateTimer(0) {
}
Player::~Player() {

}
void Player::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(64, 64);
}
void Player::Load() {
    if(playerTexture.loadFromFile("assets/images/spritesheet.png")){
        std::cout << "Player Images Loaded!" << std::endl;
        playerSprite.setTexture(playerTexture);

        int XIndex = 0;
        int YIndex = 0;

        playerSprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        playerSprite.setPosition(sf::Vector2f(0, 0));

        playerSprite.scale(sf::Vector2f(1.5, 1.5));
        boundingRectangle.setSize(sf::Vector2f(size.x * playerSprite.getScale().x, size.y * playerSprite.getScale().y));
    } else {
        std::cout << "Player image failed to loaded!" << std::endl;
    }
}
void Player::Update(float deltaTime ,Skeleton& skeleton, sf::Vector2f& mousePosition) {
    sf::Vector2f position = playerSprite.getPosition();
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= 0.75f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= 0.75f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += 0.75f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += 0.75f;

    playerSprite.setPosition(position + movement * playerSpeed * deltaTime);

    boundingRectangle.setPosition(position + movement * playerSpeed * deltaTime);
    // -------------------------------------------------------------------
    fireRateTimer += deltaTime;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireRateTimer >= maxfireRate) {
        bullets.push_back(Bullet());
        int i = bullets.size() - 1;
        bullets[i].Initialize(playerSprite.getPosition(), mousePosition, 0.5f);
        fireRateTimer = 0;
    }

    for(size_t i = 0; i < bullets.size(); i++) {
        //sf::Vector2f bulletDirection = mousePosition - bullets[i].getPosition();
        //bullets[i].setPosition(bullets[i].getPosition() + bulletDirection * bulletSpeed * deltaTime);

        bullets[i].Update(deltaTime);

        if (skeleton.health > 0) {
            if (Math::didRectCollide(bullets[i].GetGlobalBounds(), skeleton.skeletonSprite.getGlobalBounds())) {
                skeleton.ChangeHealth(-10);
                bullets.erase(bullets.begin() + i); // deleting bullets
            }
        }
    }
    // -------------------------------------------------------------------

}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(playerSprite);
    window.draw(boundingRectangle);

    for (size_t i = 0; i < bullets.size(); ++i) {
        bullets[i].Draw(window);
    }
}
