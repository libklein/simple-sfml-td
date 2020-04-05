//
// Created by patrick on 3/22/20.
//

#ifndef ROUGELIKE_DEV_ACTION_HPP
#define ROUGELIKE_DEV_ACTION_HPP

#include <fwd.hpp>

class Action {
public:
    /// Execute the action
    virtual auto execute(Unit &unit) -> bool = 0;
};


#endif //ROUGELIKE_DEV_ACTION_HPP
