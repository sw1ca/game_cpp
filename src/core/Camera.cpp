#include "../../include/core/Camera.h"
#include <algorithm>

void Camera::update(const sf::Vector2f& targetPosition) {
    float leftLimit = viewSize.x / 2.0f;
    float rightLimit = mapBounds.x - viewSize.x / 2.0f;
    float topLimit = viewSize.y / 2.0f;
    float bottomLimit = mapBounds.y - viewSize.y / 2.0f;

    sf::Vector2f center;
    center.x = std::clamp(targetPosition.x, leftLimit, rightLimit);
    center.y = std::clamp(targetPosition.y, topLimit, bottomLimit);

    view.setCenter(center);
}
void Camera::initialize(const sf::RenderWindow& window, const Map& map) {
    viewSize = sf::Vector2f(window.getSize().x, window.getSize().y);
    mapBounds = sf::Vector2f(map.getMapWidth() * map.getTileWidth(),map.getMapHeight() * map.getTileHeight());
    view.setSize(viewSize);
}

const sf::View& Camera::getView() const {
    return view;
}
