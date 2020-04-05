//
// Created by patrick on 3/29/20.
//

#ifndef ROUGELIKE_DEV_MOVEMENTACTION_HPP
#define ROUGELIKE_DEV_MOVEMENTACTION_HPP

#include <objects/actions/MovementAction.hpp>
#include <objects/Sprite.hpp>
#include <objects/Unit.hpp>

class MovementAction : public Action {
    sf::Vector2f target_;
public:
    explicit MovementAction(sf::Vector2f position) : target_(position) {};

    auto execute(Unit &unit) -> bool override {
        // check for completion
        if(unit.getPosition() == target_) return true;
        unit.moveTo(target_);
        return false;
    }

    [[nodiscard]] auto getTarget() -> sf::Vector2f;
};


#endif //ROUGELIKE_DEV_MOVEMENTACTION_HPP
