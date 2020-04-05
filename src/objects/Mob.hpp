//
// Created by patrick on 3/26/20.
//

#ifndef ROUGELIKE_DEV_MOB_HPP
#define ROUGELIKE_DEV_MOB_HPP

#include <objects/Unit.hpp>

class Mob : public Unit {
public:
    explicit Mob(Unit &&unit);
    explicit Mob(const Unit &unit);

    static auto FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Mob;

    std::unique_ptr<Sprite> constructFromPrototype() const override;
};


#endif //ROUGELIKE_DEV_MOB_HPP
