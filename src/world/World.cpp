//
// Created by patrick on 3/15/20.
//

#include "World.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

void World::update(sf::Time delta) {
    map_.update(delta);

    for(auto & entity : entities_) {
        entity->update(delta);
    }
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(map_, states);

    for(auto & entity : entities_) {
        target.draw(*entity, states);
    }
}

auto World::getMap() const -> const Map & {
    return map_;
}

auto World::getMap() -> Map & {
    return map_;
}

auto World::getEntitiesInRadius(float radius, sf::Vector2f of) const -> std::vector<const Entity *> {
    std::vector<const Entity*> in_radius;
    in_radius.reserve(entities_.size());
    for(const auto &entity_ptr : entities_) {
        if(get_absolute(entity_ptr->getPosition() - of) <= radius) {
            in_radius.push_back(entity_ptr.get());
        }
    }
    return std::move(in_radius);
}
