//
// Created by patrick on 3/18/20.
//

#ifndef ROUGELIKE_DEV_ENTITY_HPP
#define ROUGELIKE_DEV_ENTITY_HPP

#include <SFML/System/Time.hpp>
#include <objects/Sprite.hpp>
#include <objects/Animation.hpp>

/**
 * Animatable Sprite
 */
class Entity : public Sprite {
    std::optional<Animation::Animation> animation_;
public:
    using Sprite::Sprite;
    explicit Entity(Sprite&&);
    explicit Entity(const Sprite&);

    static auto FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Entity;

    std::unique_ptr<Sprite> constructFromPrototype() const override;

    /// Updates the entity's state
    virtual void update(sf::Time delta);

    /**
     * Replaces the current animation with animation.
     * @param animation
     */
    void setAnimation(Animation::Animation&& animation);

    /**
     * Replaces the current animation with animation.
     * @param animation
     */
    void setAnimation(const Animation::Animation &animation);

    /**
     * Stops and releases the current animation.
     */
    void clearAnimation();
};


#endif //ROUGELIKE_DEV_ENTITY_HPP
