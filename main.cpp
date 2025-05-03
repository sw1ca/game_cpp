#include <fmt/ranges.h>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Skeleton.h"
#include "FrameRate.h"
#include "Map.h"
#include "Boss.h"
#include "Enemy.h"
#include "Camera.h"
#include "Golem.h"

auto main() -> int {
    //-------------------------------- INITIALIZE --------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG Game", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    //-------------------------------- INITIALIZE --------------------------------
    Player player;
    Skeleton skeleton(player);
    Boss boss(player);
    Golem golem(player);
    FrameRate frameRate;
    Map map;
    Camera camera;
    // -------------------------INITIALIZE------------------------
    player.Initialize();
    skeleton.Initialize();
    boss.Initialize();
    golem.Initialize();
    frameRate.Initialize();
    map.Initialize();
    // -------------------------INITIALIZE------------------------
    // -------------------------LOAD------------------------
    player.Load();
    skeleton.Load();
    boss.Load();
    golem.Load();
    frameRate.Load();
    map.Load();
    camera.initialize(window, map);
    // -------------------------LOAD------------------------

    sf::Clock clock;
    std::vector<Enemy*> enemies = { &skeleton, &boss, &golem };

    // Load the game state
//    GameStateManager::LoadGame(player, enemies);

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

        if(player.health > 0) {
            player.Update(deltaTime, enemies, mousePosition, map, window);
            skeleton.Update(deltaTime);
            boss.Update(deltaTime);
            golem.Update(deltaTime);
        }
        camera.update(player.getPosition());
        window.setView(camera.getView());
        //-------------------------------- UPDATE --------------------------------
        //-------------------------------- DRAW --------------------------------
        window.clear(sf::Color::Black);
        map.Draw(window);
        player.Draw(window);
        skeleton.Draw(window);
        boss.Draw(window);
        golem.Draw(window);
        frameRate.Draw(window);
        window.display();
        //-------------------------------- DRAW --------------------------------
    }
    return 0;
}
