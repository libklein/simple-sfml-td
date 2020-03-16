//
// Created by patrick on 3/15/20.
//

#ifndef ROUGELIKE_DEV_TILE_HPP
#define ROUGELIKE_DEV_TILE_HPP

#include "objects/Sprite.hpp"

class Tile : public Sprite {
    bool buildable_, walkable_;

public:
    Tile(Sprite&&, bool buildable, bool walkable);
    Tile(const Sprite&, bool buildable, bool walkable);

    static auto FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Tile;

    std::unique_ptr<Sprite> constructFromPrototype() const override;
};


#endif //ROUGELIKE_DEV_TILE_HPP
