#include "Boss.h"
#include <iostream>

Boss::Boss() {
    health = 500;
}
Boss::~Boss() {}
void Boss::Initialize() {
    Enemy::Initialize();
    size = sf::Vector2i(64, 64);
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
        sprite.setPosition(sf::Vector2f(1000, 200));

        int XIndex = 3;
        int YIndex = 0;

        sprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        sprite.scale(sf::Vector2f(3, 3));

        boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
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
