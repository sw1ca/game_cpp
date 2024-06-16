#include "Boss.h"
#include <iostream>

Boss::Boss(Player& player) : Enemy(player) {
    health = 500;
}
Boss::~Boss() {}
void Boss::Initialize() {
    Enemy::Initialize();
    shootingSize = sf::Vector2i(64, 64);
    detectionSize = sf::Vector2i(300, 300);
}

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
        sprite.setPosition(sf::Vector2f(1080, 40));

        int XIndex = 3;
        int YIndex = 0;

        sprite.setTextureRect(sf::IntRect(XIndex * shootingSize.x, YIndex * shootingSize.y, shootingSize.x, shootingSize.y));
        sprite.scale(sf::Vector2f(1.8, 1.8));

        boundingRectangle.setSize(sf::Vector2f(shootingSize.x * sprite.getScale().x, shootingSize.y * sprite.getScale().y));
        detectionRectangle.setSize(sf::Vector2f(detectionSize.x * sprite.getScale().x, detectionSize.y * sprite.getScale().y));
    } else {
        std::cout << "Boss image failed to loaded!" << std::endl;
    }
}

void Boss::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}

void Boss::Draw(sf::RenderWindow &window) {
    Enemy::Draw(window);
}