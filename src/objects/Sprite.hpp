//
// Created by patrick on 3/15/20.
//

#ifndef ROUGELIKE_DEV_SPRITE_HPP
#define ROUGELIKE_DEV_SPRITE_HPP


#include <SFML/Graphics/Sprite.hpp>
#include <nlohmann/json.hpp>
#include <TextureAtlas.hpp>
#include <memory>

class Sprite : public sf::Sprite {
    std::size_t id_;
public:
    Sprite(const sf::Texture &texture, const sf::IntRect &rectangle, size_t id);

    virtual auto constructFromPrototype() const -> std::unique_ptr<Sprite>;

    auto SpriteID() const -> auto { return id_; }

    static auto FromJSON(const nlohmann::json &json, const TextureAtlas &textures) -> Sprite;
};


#endif //ROUGELIKE_DEV_SPRITE_HPP
