cmake_minimum_required(VERSION 3.27)
project(2324L_25_s31225_SR)

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

add_executable(2324L_25_s31225_SR main.cpp
        Bullet.cpp
        Bullet.h
        Math.cpp
        Math.h
        Map.cpp
        Math.h
        Tile.h
        FrameRate.cpp
        FrameRate.h
        Player.cpp
        Player.h
        Skeleton.cpp
        Skeleton.h
        Enemy.cpp
        Enemy.h
        Boss.cpp
        Boss.h
        GameStateManager.cpp
        GameStateManager.h
        Camera.h
        Camera.cpp
        Golem.h
        Golem.cpp
        EnemyConfig.h
        EnemyConfig.cpp
        Goblin.h
        Goblin.cpp
        Witch.h
)
add_custom_command(
        TARGET 2324L_25_s31225_SR POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:2324L_25_s31225_SR>/assets
)
target_link_libraries(2324L_25_s31225_SR fmt)
target_link_libraries(2324L_25_s31225_SR sfml-graphics)

