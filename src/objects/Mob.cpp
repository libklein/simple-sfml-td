//
// Created by patrick on 3/26/20.
//

#include "Mob.hpp"

auto Mob::FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Mob {
    return Mob(Unit::FromJSON(data, textures));
}

Mob::Mob(Unit &&unit) : Unit(std::move(unit)) {

}

Mob::Mob(const Unit &unit) : Unit(unit) {

}

std::unique_ptr<Sprite> Mob::constructFromPrototype() const {
    return std::make_unique<Mob>(*this);
}
