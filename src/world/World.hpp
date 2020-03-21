//
// Created by patrick on 3/15/20.
//

#ifndef ROUGELIKE_DEV_WORLD_HPP
#define ROUGELIKE_DEV_WORLD_HPP

#include <world/Map.hpp>

/**
 * Keep track of whatever is in the world.
 */
class World {
    Map map_;

public:
    explicit World(Map &&map) : map_(std::move(map)) {}
};


#endif //ROUGELIKE_DEV_WORLD_HPP
