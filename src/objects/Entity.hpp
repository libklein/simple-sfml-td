//
// Created by patrick on 3/18/20.
//

#ifndef ROUGELIKE_DEV_ENTITY_HPP
#define ROUGELIKE_DEV_ENTITY_HPP

#include <SFML/System/Time.hpp>
#include <objects/Sprite.hpp>
#include <objects/Animation.hpp>
#include <fwd.hpp>

/**
 * Animatable Sprite
 */
class Entity : public Sprite {
    World *world_; /// An entity lives in a world

    std::optional<Animation::Animation> animation_ = std::nullopt;
public:
    using Sprite::Sprite;
    explicit Entity(Sprite&&);
    explicit Entity(const Sprite&);

    static auto FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Entity;
    std::unique_ptr<Sprite> constructFromPrototype() const override;

    /// Updates the entity's state
    virtual void update(sf::Time delta);

    [[nodiscard]] virtual auto isAlive() const -> bool { return true; };

    // TODO Get rid of this. Move to constructor, it should be an invariant of entities that world is always valid.
    void setWorld(World *world);

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

protected:
    [[nodiscard]] auto getWorld() -> World*;
    [[nodiscard]] auto getWorld() const -> World *;
};


#endif //ROUGELIKE_DEV_ENTITY_HPP
