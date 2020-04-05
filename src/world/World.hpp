//
// Created by patrick on 3/15/20.
//

#ifndef ROUGELIKE_DEV_WORLD_HPP
#define ROUGELIKE_DEV_WORLD_HPP

#include <world/Map.hpp>
#include <objects/Entity.hpp>
#include <SpriteFactory.hpp>
#include <util/pool.hpp>

/**
 * Keep track of whatever is in the world.
 */
class World : public sf::Drawable {
    const SpriteFactory *sprite_factory_;
    Map map_;
    // TODO Dynamic iterable pool
    // TODO Just rewrite pool allocator to adhere to allocator pattern...
    //util::iterable_pool<Entity> entities_; /// Entities living in the world
    std::vector<std::unique_ptr<Entity>> entities_;
public:
    World(Map &&map, const SpriteFactory &sprite_factory) : map_(std::move(map)), sprite_factory_(&sprite_factory) {}
    World(const World &other) = delete;
    World& operator=(const World &other) = delete;
    World(World &&other) noexcept = default;
    World& operator=(World &&other) noexcept = default;

    // Getters
    [[nodiscard]] auto getMap() const -> const Map&;
    [[nodiscard]] auto getMap() -> Map&;
    [[nodiscard]] auto getSpriteFactory() const -> const SpriteFactory& { return *sprite_factory_; };

    // Computed
    [[nodiscard]] auto getEntitiesInRadius(float radius, sf::Vector2f of) const -> std::vector<const Entity*>;

    /// Spawn a unit
    template<class T>
    auto spawn(std::unique_ptr<T> entity, float x, float y) -> T& {
        auto &local_entity = *entity;
        entities_.push_back(std::move(entity));
        local_entity.setWorld(this);
        local_entity.setPosition(x, y);
        return local_entity;
    };
    /// Spawn a unit
    template<class T>
    auto spawn(SpriteFactory::SpriteID entity_prototype_id, float x, float y) -> T& {
        auto unit = sprite_factory_->CreateEntity<T>(entity_prototype_id);
        return spawn(std::move(unit), x, y);
    }

    void update(sf::Time delta);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //ROUGELIKE_DEV_WORLD_HPP
