//
// Created by patrick on 3/15/20.
//

#include "World.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

void World::update(sf::Time delta) {
    // Remove all entities that were killed in the last update
    this->remove_killed_entities();

    // Moved killed entities into killed_entities
    decltype(entities_)::size_type index = 0;
    for(auto next_entity = entities_.begin(); next_entity != entities_.end();++next_entity, ++index) {
        if(!next_entity->get()->isAlive()) {
            killed_entities_.push_back(index);
        }
    }

    map_.update(delta);

    for(auto & entity : entities_) {
        entity->update(delta);
    }

    this->flush_spawn_queue();
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

auto World::getEntitiesInRadius(float radius, sf::Vector2f of) const -> std::vector<Entity *> {
    std::vector<Entity*> in_radius;
    in_radius.reserve(entities_.size());
    for(const auto &entity_ptr : entities_) {
        if(get_absolute(entity_ptr->getPosition() - of) <= radius) {
            in_radius.push_back(entity_ptr.get());
        }
    }
    return std::move(in_radius);
}

void World::remove_killed_entities() {
    // Remove all entities that have been marked as "killed" from the world.
    assert(entities_.size() >= killed_entities_.size());
    auto next_position = entities_.end() - 1;
    // Sort in asceding order - this way we prevent swapping killed with killed entities.
    std::sort(killed_entities_.begin(), killed_entities_.end(), [](auto lhs, auto rhs){return lhs > rhs;});
    for(size_t next_killed_entitiy_index : killed_entities_) {
        std::iter_swap(entities_.begin() + next_killed_entitiy_index, next_position);
        --next_position;
    }
    entities_.erase(std::next(next_position), entities_.end());
    killed_entities_.clear();
}

void World::flush_spawn_queue() {
    // Move entities from the spawn queue into the actual world
    // As we save the id's of entities killed during the current iteration of the game loop
    // it is imperative to add them to the end. Otherwise they will invalidate the saved indices.
    auto first_moved_entity = entities_.insert(entities_.end(),
                                               std::make_move_iterator(spawn_queue_.begin()),
                                               std::make_move_iterator(spawn_queue_.end()));
    spawn_queue_.clear();
    // TODO Notify everyone who requested spawning.
}

void World::removeFromWorld(const Entity *entity) {
    // Determine entity id
    auto entity_iter = std::find_if(entities_.begin(), entities_.end(), [entity](const auto &other_entity) {
        return entity == other_entity.get();
    });
    assert(entity_iter != entities_.end());
    killed_entities_.push_back(std::distance(entities_.begin(), entity_iter));
}
