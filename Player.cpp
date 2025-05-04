#include "Player.h"
#include "Math.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Mouse.hpp"
#include <iostream>

Player::Player() : health(200), playerSpeed(1.f), maxfireRate(150), fireRateTimer(0) {}
Player::~Player() {}

void Player::ChangeHealth(int hp) {
    health += hp;
    healthText.setString(std::to_string(health));
}
void Player::setPosition(sf::Vector2f position) {
    playerSprite.setPosition(position);
    boundingRectangle.setPosition(position);
}
void Player::Move(Map &map, sf::Vector2f direction, float deltaTime) {
    sf::Vector2f newPosition = playerSprite.getPosition() + direction * playerSpeed * deltaTime;

    if (!map.IsBlocked(newPosition.x, newPosition.y)) {
        playerSprite.setPosition(newPosition);
        boundingRectangle.setPosition(newPosition);
    }
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

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("GAME OVER!");
}
void Player::Load() {
    if(font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "Arial.ttf font has been loaded successfully" << std::endl;
        healthText.setFont(font);
        healthText.setCharacterSize(15);
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
        playerSprite.setPosition(sf::Vector2f(10, 2000));

        playerSprite.scale(sf::Vector2f(0.8, 0.8));
        boundingRectangle.setSize(sf::Vector2f(size.x * playerSprite.getScale().x, size.y * playerSprite.getScale().y));
    } else {
        std::cout << "Player image failed to loaded!" << std::endl;
    }
}
void Player::Update(float deltaTime, std::vector<Enemy*>& enemies, sf::Vector2f& mousePosition, Map& map, sf::RenderWindow& window, std::vector<HealthPack>& healthPack) {
    if(health > 0) {
        sf::Vector2f position = playerSprite.getPosition();
        healthText.setPosition(playerSprite.getPosition().x + boundingRectangle.getSize().x / 4, playerSprite.getPosition().y - 10);
        sf::Vector2f movement(0.f, 0.f);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= 0.20f;
            playerSprite.setTextureRect(goUpTexture);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= 0.20f;
            playerSprite.setTextureRect(goLeftTexture);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += 0.20f;
            playerSprite.setTextureRect(goDownTexture);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += 0.20f;
            playerSprite.setTextureRect(goRightTexture);
        }

        if(movement != sf::Vector2f(0.f, 0.f)) {
            map.MovePlayer(*this, movement);
        }

        Move(map, movement, deltaTime);

        boundingRectangle.setPosition(position + movement * playerSpeed * deltaTime);
        // -------------------------------------------------------------------
        fireRateTimer += deltaTime;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireRateTimer >= maxfireRate) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f adjustedMousePosition = window.mapPixelToCoords(mousePosition);
            bullets.push_back(Bullet());
            int i = bullets.size() - 1;
            bullets[i].Initialize(playerSprite.getPosition(), adjustedMousePosition, 0.5f);
            fireRateTimer = 0;
        }

        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].Update(deltaTime);

            for (Enemy *enemy : enemies) {
                if (enemy->health > 0) {
                    if (Math::didRectCollide(bullets[i].GetGlobalBounds(), enemy->GetGlobalBounds())) {
                        enemy->ChangeHealth(-10);
                        bullets.erase(bullets.begin() + i); // deleting bullets
                    }
                }
            }
        }
        checkHealthPackCollision(healthPack);
    }
    // -------------------------------------------------------------------

}

void Player::Draw(sf::RenderWindow& window) {
    if (health > 0) {
        window.draw(playerSprite);
        //window.draw(boundingRectangle);
        window.draw(healthText);

        for (size_t i = 0; i < bullets.size(); ++i) {
            bullets[i].Draw(window);
        }
    }else{
        sf::View currentView = window.getView();
        window.setView(window.getDefaultView());
        sf::Vector2u windowSize = window.getSize();
        gameOverText.setPosition(
                windowSize.x / 2.f - gameOverText.getGlobalBounds().width / 2.f,
                windowSize.y / 2.f - gameOverText.getGlobalBounds().height / 2.f
        );

        window.draw(gameOverText);
        window.setView(currentView);
    }
}

sf::Vector2f Player::getPosition() const {
    return playerSprite.getPosition();
}

sf::RectangleShape Player::getBoundingRectanglePosition() const {
    return boundingRectangle;
}
void Player::checkHealthPackCollision(std::vector<HealthPack> &healthPacks) {
    for (auto &healthPack: healthPacks) {
        if (healthPack.isActive() && health < 200) {
            if (boundingRectangle.getGlobalBounds().intersects(healthPack.getGlobalBounds())) {
                health = std::min(health + HealthPack::getHealAmount(), 200.f);
                healthText.setString(std::to_string(health));
                healthPack.setActive(false);
            }
        }
    }
}