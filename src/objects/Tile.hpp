//
// Created by patrick on 3/15/20.
//

#ifndef ROUGELIKE_DEV_TILE_HPP
#define ROUGELIKE_DEV_TILE_HPP

#include "objects/Sprite.hpp"
#include <objects/Entity.hpp>

class Tile : public Sprite {
protected:
    bool buildable_, walkable_;

    // Entity residing on tile
    Entity *entity_;
public:
    Tile(Sprite&&, bool buildable, bool walkable);
    Tile(const Sprite&, bool buildable, bool walkable);

    void setEntity(Entity *entity);
    auto getEntity() -> Entity*;
    auto getEntity() const -> const Entity*;
    auto releaseEntity() -> Entity*;

    static auto FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Tile;

    auto canBuild() const -> bool;

    auto hasEntity() const -> bool;

    std::unique_ptr<Sprite> constructFromPrototype() const override;
};


#endif //ROUGELIKE_DEV_TILE_HPP
