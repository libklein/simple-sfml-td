//
// Created by patrick on 3/15/20.
//

#include "Tile.hpp"

std::unique_ptr<Sprite> Tile::constructFromPrototype() const {
    return std::make_unique<Tile>(*this);
}

Tile::Tile(Sprite&& sprite, bool buildable, bool walkable)
    : Sprite(std::move(sprite)), buildable_(buildable), walkable_(walkable) {}

Tile::Tile(const Sprite &sprite, bool buildable, bool walkable)
        : Sprite(sprite), buildable_(buildable), walkable_(walkable) {}

auto Tile::FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Tile {
    return Tile(Sprite::FromJSON(data, textures), data["buildable"], data["walkable"]);
}

void Tile::setEntity(Entity *entity) {
    entity_ = entity;
}

auto Tile::canBuild() const -> bool {
    return buildable_ && !entity_;
}

auto Tile::hasEntity() const -> bool {
    return entity_;
}

auto Tile::getEntity() -> Entity * {
    return entity_;
}

auto Tile::getEntity() const -> const Entity * {
    return entity_;
}

auto Tile::releaseEntity() -> Entity * {
    Entity *entity = nullptr;
    std::swap(entity, entity_);
    return entity;
}
