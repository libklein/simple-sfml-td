//
// Created by patrick on 3/18/20.
//

#include "Entity.hpp"

Entity::Entity(Sprite &&sprite)
    : Sprite(std::move(sprite)) {

}

Entity::Entity(const Sprite &sprite)
    : Sprite(sprite) {

}

auto Entity::FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Entity {
    //return Entity(std::move(Sprite::FromJSON(data, textures)), false, false);
    return Entity(std::move(Sprite::FromJSON(data, textures)));
}

std::unique_ptr<Sprite> Entity::constructFromPrototype() const {
    return std::make_unique<Entity>(*this);
}
