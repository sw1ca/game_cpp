🏜️ 2D RPG GAME

A 2D Action-RPG game engine built from scratch using C++ and SFML. The project demonstrates custom collision detection systems, enemy AI behaviors, and map generated with "Tiled".

# 📖 About The Project

In this game, the player controls a Skeleton warrior exploring an ancient, desert-themed world. The goal is to survive and kill enemies, bosses encountered along the way and upgrade the character's stats.

The main focus of this project was to implement core game development concepts in C++ without relying on heavy game engines (like Unity or Unreal), to deeply understand memory management, rendering loops, and object-oriented programming patterns.

# 🧠 Enemy AI & Combat System
* Dual-Layer Collision System:
    * Detection Box (Aggro): A larger invisible hitbox used for AI awareness. When the player enters this zone, enemies switch state from `Idle` to `Attack`.
    * Hitbox (Physics): A smaller hitbox strictly for damage calculation.
* Enemy Classes:
    * Melee: Pathfinds towards the player until close enough to strike.
    * Ranged: Maintains distance and fires bullets upon detection.
    * Bosses: Stronger variants with higher HP, damage output, and exclusive drops (Strength Potions).

# 🗺️ Map & World
* Tiled Integration: Maps designed in Tiled software and imported into the engine.
* Camera System: Dynamic camera locked on the player creates a scrolling world effect.
* Collision Map: Specific tiles (water, buildings, vegetation) are parsed as non-walkable obstacles.

# 💾 Persistence (Save/Load)
* Serialization: The game supports saving the current state (Player HP, Position, Stats) to a file and restoring it later.
    * `F1`: Save Game state.
    * `F2`: Load Game state.

# 🧪 RPG Elements
* Health Potions: Restore 50 HP (capped at 200 Max HP). Scattered around the map.
* Strength Potions: Rare drop from Bosses. Permanently increases damage by 5.

# 🛠️ Tech Stack

* Language: C++ (Standard 20)
* Graphics: [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)
* Map Editor: Tiled

# 🎮 Controls

| Key | Action |
| :--- | :--- |
| W, A, S, D | Movement |
| MOUSE BUTTON 1 | Shoot |
| F1 | Save Game |
| F2 | Load Game |

# 🤝 Credits

* Code & Logic: Rafał Święcicki
* Assets: Tilesets and Sprites provided by (https://opengameart.org/)

---
*This project was created as part of the Computer Science curriculum at PJAIT (Polish-Japanese Academy of Information Technology).*
