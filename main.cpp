#include <fmt/ranges.h>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Boss.h"
#include "Golem.h"
#include "Goblin.h"
#include "Witch.h"
#include "Beaver.h"
#include "Nocturne.h"
#include "Mage.h"
#include "FrameRate.h"
#include "Camera.h"

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
        auto healthPack = std::make_unique<HealthPack>();
        healthPack->Load();
        healthPack->Initialize(position);
        elixirs.push_back(std::move(healthPack));
    }
    FrameRate frameRate;
    Map map;
    Camera camera;
    // -------------------------INITIALIZE------------------------
    player.Initialize();
    skeleton.Initialize();
    boss.Initialize();
    golem.Initialize();
    goblin.Initialize();
    witch.Initialize();
    beaver.Initialize();
    nocturne.Initialize();
    mage.Initialize();
    frameRate.Initialize();
    map.Initialize();
    // -------------------------INITIALIZE------------------------
    // -------------------------LOAD------------------------
    player.Load();
    skeleton.Load();
    boss.Load();
    golem.Load();
    goblin.Load();
    witch.Load();
    beaver.Load();
    nocturne.Load();
    mage.Load();
    frameRate.Load();
    map.Load();
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

        frameRate.Update(deltaTime);
        map.Update(deltaTime);

        if(player.health > 0) {
            player.Update(deltaTime, enemies, mousePosition, map, window, elixirs);
            skeleton.Update(deltaTime);
            boss.Update(deltaTime);
            golem.Update(deltaTime);
            goblin.Update(deltaTime);
            witch.Update(deltaTime);
            beaver.Update(deltaTime);
            nocturne.Update(deltaTime);
            mage.Update(deltaTime);
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
        goblin.Draw(window);
        witch.Draw(window);
        beaver.Draw(window);
        nocturne.Draw(window);
        mage.Draw(window);
        for (const auto& elixir : elixirs) {
            if (elixir->isActive()) {
                elixir->Draw(window);
            }
        }
        frameRate.Draw(window);
        window.display();
        //-------------------------------- DRAW --------------------------------
    }
    return 0;
}
