#include "fmt/ranges.h"
#include "SFML/Graphics.hpp"

#include "../include/entities/Player.h"
#include "../include/entities/Skeleton.h"
#include "../include/entities/Boss.h"
#include "../include/entities/Golem.h"
#include "../include/entities/Goblin.h"
#include "../include/entities/Witch.h"
#include "../include/entities/Beaver.h"
#include "../include/entities/Nocturne.h"
#include "../include/entities/Mage.h"
#include "../include/core/FrameRate.h"
#include "../include/core/Camera.h"

auto main() -> int {
    //-------------------------------- INITIALIZE --------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RPG Game", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    //-------------------------------- INITIALIZE --------------------------------
    Player player;
    Skeleton skeleton(player);
    Boss boss(player);
    Golem golem(player);
    Goblin goblin(player);
    Witch witch(player);
    Beaver beaver(player);
    Nocturne nocturne(player);
    Mage mage(player);
    std::vector<std::unique_ptr<Elixir>> elixirs;
    const std::vector<sf::Vector2f> healthPackPositions = {
            {1345, 1550},
            {900, 755},
            {2880, 1055}
    };
    for (const auto& position : healthPackPositions) {
        auto healthPack = std::make_unique<HealthElixir>();
        healthPack->load();
        healthPack->initialize(position);
        elixirs.push_back(std::move(healthPack));
    }
    FrameRate frameRate;
    Map map;
    Camera camera;
    // -------------------------INITIALIZE------------------------
    player.initialize();
    skeleton.initialize();
    boss.initialize();
    golem.initialize();
    goblin.initialize();
    witch.initialize();
    beaver.initialize();
    nocturne.initialize();
    mage.initialize();
    frameRate.initialize();
    map.initialize();
    // -------------------------INITIALIZE------------------------
    // -------------------------LOAD------------------------
    player.load();
    skeleton.load();
    boss.load();
    golem.load();
    goblin.load();
    witch.load();
    beaver.load();
    nocturne.load();
    mage.load();
    frameRate.load();
    map.load();
    camera.initialize(window, map);
    // -------------------------LOAD------------------------

    sf::Clock clock;
    std::vector<Enemy*> enemies = { &skeleton, &boss, &golem, &goblin, &witch, &beaver, &nocturne, &mage };


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

        frameRate.update(deltaTime);
        map.update(deltaTime);

        if(player.health > 0) {
            player.update(deltaTime, enemies, mousePosition, map, window, elixirs);
            skeleton.update(deltaTime);
            boss.update(deltaTime);
            golem.update(deltaTime);
            goblin.update(deltaTime);
            witch.update(deltaTime);
            beaver.update(deltaTime);
            nocturne.update(deltaTime);
            mage.update(deltaTime);
        }
        camera.update(player.getPosition());
        window.setView(camera.getView());
        //-------------------------------- UPDATE --------------------------------
        //-------------------------------- DRAW --------------------------------
        window.clear(sf::Color::Black);
        map.draw(window);
        player.draw(window);
        skeleton.draw(window);
        boss.draw(window);
        golem.draw(window);
        goblin.draw(window);
        witch.draw(window);
        beaver.draw(window);
        nocturne.draw(window);
        mage.draw(window);
        for (const auto& elixir : elixirs) {
            if (elixir->isActive()) {
                elixir->draw(window);
            }
        }
        frameRate.draw(window);
        window.display();
        //-------------------------------- DRAW --------------------------------
    }
    return 0;
}
