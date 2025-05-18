cmake_minimum_required(VERSION 3.27)
project(2425S_18_s31225_ZJ)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(fmt)

add_executable(2425S_18_s31225_ZJ src/main.cpp
        src/core/Bullet.cpp
        include/core/Bullet.h
        src/core/Math.cpp
        include/core/Math.h
        src/map/Map.cpp
        include/core/Math.h
        include/map/Tile.h
        src/core/FrameRate.cpp
        include/core/FrameRate.h
        src/entities/Player.cpp
        include/entities/Player.h
        include/entities/Skeleton.h
        src/entities/Enemy.cpp
        include/entities/Enemy.h
        include/entities/Boss.h
        include/core/Camera.h
        src/core/Camera.cpp
        include/entities/Golem.h
        include/config/EnemyConfig.h
        include/entities/Goblin.h
        src/entities/Goblin.cpp
        include/entities/Witch.h
        include/entities/Beaver.h
        src/entities/Beaver.cpp
        include/entities/Nocturne.h
        include/entities/Mage.h
        include/items/HealthElixir.h
        src/items/HealthElixir.cpp
        include/items/Elixir.h
        src/items/Elixir.cpp
        src/items/StrengthElixir.cpp
        include/items/StrengthElixir.h
        include/config/ElixirConfig.h
        include/core/GameStateManager.h
        src/core/GameStateManager.cpp
)
add_custom_command(
        TARGET 2425S_18_s31225_ZJ POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:2425S_18_s31225_ZJ>/assets
)
target_link_libraries(2425S_18_s31225_ZJ fmt)
target_link_libraries(2425S_18_s31225_ZJ sfml-graphics)

