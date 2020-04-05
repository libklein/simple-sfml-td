cmake_minimum_required(VERSION 3.15)
project(rougelike_dev)

set(CMAKE_CXX_STANDARD 20)

add_executable(rougelike_dev src/main.cpp src/TextureAtlas.cpp src/TextureAtlas.hpp src/world/Map.cpp src/world/Map.hpp src/SpriteFactory.cpp src/SpriteFactory.hpp src/world/World.cpp src/world/World.hpp src/objects/Sprite.cpp src/objects/Sprite.hpp src/objects/Tile.cpp src/objects/Tile.hpp src/objects/Entity.cpp src/objects/Entity.hpp src/util/pool.hpp src/objects/actors/Command.cpp src/objects/actors/Command.hpp src/objects/Animation.cpp src/objects/Animation.hpp src/objects/actions/Action.cpp src/objects/actions/Action.hpp src/objects/actors/CommandReceiver.cpp src/objects/actors/CommandReceiver.hpp src/objects/actors/CommandEmitter.cpp src/objects/actors/CommandEmitter.hpp src/fwd.hpp src/objects/Unit.cpp src/objects/Unit.hpp src/objects/Tower.cpp src/objects/Tower.hpp src/objects/Mob.cpp src/objects/Mob.hpp src/util/math.h src/objects/actions/MovementAction.cpp src/objects/actions/MovementAction.hpp src/game/Game.cpp src/game/Game.hpp src/game/Wave.cpp src/game/Wave.hpp)

target_include_directories(rougelike_dev PRIVATE src/)
target_include_directories(rougelike_dev PRIVATE lib/)

target_link_libraries(rougelike_dev sfml-graphics sfml-window sfml-system)