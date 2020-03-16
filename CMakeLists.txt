cmake_minimum_required(VERSION 3.15)
project(rougelike_dev)

set(CMAKE_CXX_STANDARD 20)

add_executable(rougelike_dev src/main.cpp src/TextureAtlas.cpp src/TextureAtlas.hpp src/world/Map.cpp src/world/Map.hpp src/SpriteAtlas.cpp src/SpriteAtlas.hpp src/world/World.cpp src/world/World.hpp src/objects/Sprite.cpp src/objects/Sprite.hpp src/objects/Tile.cpp src/objects/Tile.hpp)

target_include_directories(rougelike_dev PRIVATE src/)
target_include_directories(rougelike_dev PRIVATE lib/)

target_link_libraries(rougelike_dev sfml-graphics sfml-window sfml-system)