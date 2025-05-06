#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Map.h"
#pragma once

class Camera {
private:
    sf::View view;
    sf::Vector2f mapBounds;
    sf::Vector2f viewSize;

public:
    Camera() = default;
    void initialize(const sf::RenderWindow& window, const Map& map);
    void update(const sf::Vector2f& targetPosition);
    const sf::View& getView() const;
};

