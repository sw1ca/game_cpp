#include "Skeleton.h"
#include <iostream>

Skeleton::Skeleton(Player& player) : Enemy(player) {
    health = 100;
}
Skeleton::~Skeleton() {}

void Skeleton::Initialize() {
    Enemy::Initialize();
    shootingSize = sf::Vector2i(64, 64);
    detectionSize = sf::Vector2i(600, 600);
}
void Skeleton::Load() {
    if(font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "Arial.ttf font has been loaded successfully" << std::endl;
        healthText.setFont(font);
        healthText.setCharacterSize(15);
        healthText.setString(std::to_string(health));
    }else{
        std::cout << "Failed to load Arial.ttf font" << std::endl;
    }

    if(texture.loadFromFile("assets/images/spritesheet.png")){
        std::cout << "Skeleton Images Loaded!" << std::endl;
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(300, 1500));

        int XIndex = 0;
        int YIndex = 2;

        sprite.setTextureRect(sf::IntRect(XIndex * shootingSize.x, YIndex * shootingSize.y, shootingSize.x, shootingSize.y));
        sprite.scale(sf::Vector2f(0.8, 0.8));

        boundingRectangle.setSize(sf::Vector2f(shootingSize.x * sprite.getScale().x, shootingSize.y * sprite.getScale().y));
        detectionRectangle.setSize(sf::Vector2f(detectionSize.x * sprite.getScale().x, detectionSize.y * sprite.getScale().y));
    } else {
        std::cout << "Skeleton image failed to loaded!" << std::endl;
    }
}
void Skeleton::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}
void Skeleton::Draw(sf::RenderWindow& window) {
    Enemy::Draw(window);
}
