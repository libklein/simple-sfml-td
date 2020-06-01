//
// Created by patrick on 3/29/20.
//

#include "Wave.hpp"
#include <world/World.hpp>
#include <util/utility.hpp>

void Wave::update(sf::Time delta) {
    time_since_last_group_ += delta;
    if(time_since_last_group_ >= prototype_.group_delay && !spawnedAllMobs()) {
        // Spawn next group
        size_t spawned_enemies = 0;
        const auto &spawn_points = world_->getMap().getSpawnPoints();
        while(spawned_enemies < prototype_.group_size && !spawnedAllMobs()) {
            // Choose spawn point
            const Tile *spawn_point = spawn_points[spawned_enemies % spawn_points.size()];

            auto &mob = world_->spawn<Mob>(prototype_.mobs.back(),
                    spawn_point->getPosition().x, spawn_point->getPosition().y);

            // Give movement command - choose closest location
            auto &shortest_path = *std::min_element(paths_.begin(), paths_.end(),
                                                    [&spawn_point](auto &path, auto &alt_path) {
                                                        return get_absolute(path->getTarget() - spawn_point->getPosition()) <
                                                               get_absolute(alt_path->getTarget() - spawn_point->getPosition());
                                                    });

            mob.setAction(shortest_path);
            mobs_.push_back(&mob);
            prototype_.mobs.pop_back();
            spawned_enemies++;
        }
        time_since_last_group_ = sf::Time::Zero;
    }
    // Check which entities
    for(auto next_mob = mobs_.begin(); next_mob != mobs_.end();) {
        if(!(*next_mob)->isAlive()) {
            util::unordered_remove(mobs_, next_mob);
            continue;
        }
        if(_is_mob_at_target(**next_mob)) {
            // TODO Notify game
            world_->removeFromWorld(*next_mob);
            util::unordered_remove(mobs_, next_mob);
            continue;
        }
        ++next_mob;
    }
}

auto Wave::_find_spawn_point_with_no_collision(SpriteFactory::SpriteID next_mob) const -> std::optional<sf::Vector2f> {
    for(const Tile *spawn_point : world_->getMap().getSpawnPoints()) {
        auto entites_close_to_spawn = world_->getEntitiesInRadius(
                std::max(sprites_->getSprite(next_mob).getSize().x, sprites_->getSprite(next_mob).getSize().y) - 1,
                spawn_point->getPosition());
        if(entites_close_to_spawn.empty()) {
            return spawn_point->getPosition();
        }
    }
    return std::nullopt;
}

Wave::Wave(WavePrototype prototype, World &world, const SpriteFactory &sprites, sf::Time start_time)
    : prototype_(std::move(prototype)), world_(&world), sprites_(&sprites), start_time_(start_time)
    , time_since_last_group_(prototype_.group_delay) {
    for(const Tile *tile_ptr : world_->getMap().getTargets()) {
        paths_.push_back(std::make_shared<MovementAction>(tile_ptr->getPosition()));
    }
}

auto Wave::getFinishTime() const -> sf::Time {
    return *finish_time_;
}

auto Wave::getStartTime() const -> sf::Time {
    return start_time_;
}

auto Wave::spawnedAllMobs() const -> bool {
    return prototype_.mobs.empty();
}

auto Wave::finished() const -> bool {
    return spawnedAllMobs() && mobs_.empty();
}

auto Wave::_is_mob_at_target(const Mob &mob) const -> bool {
    return std::find_if(world_->getMap().getTargets().begin(), world_->getMap().getTargets().end(), [&mob](const auto &tile) {
        return get_distance(mob, *tile) < 5;
    }) != world_->getMap().getTargets().end();
}
