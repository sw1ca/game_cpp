#include <fmt/ranges.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Skeleton.h"
#include "FrameRate.h"
#include "Map.h"
#include "Boss.h"
#include "Enemy.h"

auto main() -> int {
    //-------------------------------- INITIALIZE --------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1600, 900), "RPG Game", sf::Style::Default, settings);
    window.setFramerateLimit(360);
    //-------------------------------- INITIALIZE --------------------------------
    Player player;
    Skeleton skeleton;
    Boss boss;
    FrameRate frameRate;
    Map map;
    // -------------------------INITIALIZE------------------------
    player.Initialize();
    skeleton.Initialize();
    boss.Initialize();
    frameRate.Initialize();
    map.Initialize();
    // -------------------------INITIALIZE------------------------
    // -------------------------LOAD------------------------
    player.Load();
    skeleton.Load();
    boss.Load();
    frameRate.Load();
    map.Load();
    // -------------------------LOAD------------------------

    sf::Clock clock;
    std::vector<Enemy*> enemies = { &skeleton, &boss };

    //main game loop
    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;
        // 1 second = 1 000 milliseconds
        // 1 millisecond = 1 000 microseconds
        //-------------------------------- UPDATE --------------------------------
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

        frameRate.Update(deltaTime);
        map.Update(deltaTime);
        player.Update(deltaTime, enemies, mousePosition);
        skeleton.Update(deltaTime);
        boss.Update(deltaTime);

        for(auto* enemy : enemies) {
            if (enemy -> CheckPlayerDetectionCollision(player.getBoundingRectanglePosition())) {
                std::cout << "Enemy starts shooting player" << std::endl;
            }
        }
        //-------------------------------- UPDATE --------------------------------
        //-------------------------------- DRAW --------------------------------
        window.clear(sf::Color::Black);
        map.Draw(window);
        player.Draw(window);
        skeleton.Draw(window);
        boss.Draw(window);
        frameRate.Draw(window);
        window.display();
        //-------------------------------- DRAW --------------------------------
    }
    return 0;
}
