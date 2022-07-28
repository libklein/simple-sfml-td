//
// Created by patrick on 6/1/20.
//

#ifndef ROUGELIKE_DEV_PROJECTILE_HPP
#define ROUGELIKE_DEV_PROJECTILE_HPP

#include "Unit.hpp"

class Projectile : public Unit {
public:
    Projectile(Entity&& entity, float max_speed, float max_turn_speed);
};


#endif //ROUGELIKE_DEV_PROJECTILE_HPP
