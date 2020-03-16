//
// Created by patrick on 3/15/20.
//

#include "Sprite.hpp"

auto Sprite::constructFromPrototype() const -> std::unique_ptr<Sprite> {
    return std::make_unique<Sprite>(*this);
}

auto Sprite::FromJSON(const nlohmann::json &json, const TextureAtlas &textures) -> Sprite {
    return Sprite(textures.Texture(), textures.getCoord<int>(json["sprite_id"]), json["uuid"]);
}

Sprite::Sprite(const sf::Texture &texture, const sf::IntRect &rectangle, size_t id) : sf::Sprite(texture, rectangle),
                                                                                      id_(id) {}
