#include "../../include/core/Bullet.h"
#include "../../include/core/Math.h"
Bullet::Bullet() : speed(0) {}

Bullet::~Bullet() {}

void Bullet::Initialize(const sf::Vector2f& position, sf::Vector2f& target, float speed) {
    this -> speed = speed;
    circleShape.setRadius(5.0f);
    circleShape.setPosition(position);
    direction = Math::NormalizeVector(target - position);
}

void Bullet::Update(float deltaTime) {
    circleShape.setPosition(circleShape.getPosition() + direction * speed * deltaTime);
}

void Bullet::Draw(sf::RenderWindow &window) {
    window.draw(circleShape);
}
void Bullet::setBulletSize(const float radius) {
    circleShape.setRadius(radius);
}
void Bullet::setBulletColor(const sf::Color &color) {
    circleShape.setFillColor(color);
}

