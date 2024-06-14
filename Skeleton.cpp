#include "Skeleton.h"
#include <iostream>

Skeleton::Skeleton() : health(100) {

}
Skeleton::~Skeleton() {

}
void Skeleton::ChangeHealth(int hp) {
    health += hp;
    healthText.setString(std::to_string(health));
}
void Skeleton::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Blue);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(64, 64);
}
void Skeleton::Load() {
    if(font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "Arial.ttf font has been loaded successfully" << std::endl;
        healthText.setFont(font);
        healthText.setString(std::to_string(health));
    }else{
        std::cout << "Failed to load Arial.ttf font" << std::endl;
    }

    if(skeletonTexture.loadFromFile("assets/images/spritesheet.png")){
        std::cout << "Skeleton Images Loaded!" << std::endl;
        skeletonSprite.setTexture(skeletonTexture);
        skeletonSprite.setPosition(sf::Vector2f(1100, 550));

        int XIndex = 0;
        int YIndex = 2;

        skeletonSprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        skeletonSprite.scale(sf::Vector2f(1.5, 1.5));

        boundingRectangle.setSize(sf::Vector2f(size.x * skeletonSprite.getScale().x, size.y * skeletonSprite.getScale().y));
    } else {
        std::cout << "Skeleton image failed to loaded!" << std::endl;
    }
}
void Skeleton::Update(float deltaTime) {
    if(health > 0) {
        boundingRectangle.setPosition(skeletonSprite.getPosition());
        healthText.setPosition(skeletonSprite.getPosition());
    }
}
void Skeleton::Draw(sf::RenderWindow& window) {
    if(health > 0) {
        window.draw(skeletonSprite);
        window.draw(boundingRectangle);
        window.draw(healthText);
    }
}

