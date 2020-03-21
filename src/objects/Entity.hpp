//
// Created by patrick on 3/18/20.
//

#ifndef ROUGELIKE_DEV_ENTITY_HPP
#define ROUGELIKE_DEV_ENTITY_HPP

#include <SFML/System/Time.hpp>
#include <objects/Sprite.hpp>

class Entity : public Sprite {
public:
    virtual void update(sf::Time delta) {};

    using Sprite::Sprite;
    Entity(Sprite&&);
    Entity(const Sprite&);

    static auto FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Entity;

    std::unique_ptr<Sprite> constructFromPrototype() const override;
};


#endif //ROUGELIKE_DEV_ENTITY_HPP
