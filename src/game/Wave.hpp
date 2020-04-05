//
// Created by patrick on 3/29/20.
//

#ifndef ROUGELIKE_DEV_WAVE_HPP
#define ROUGELIKE_DEV_WAVE_HPP

#include <SpriteFactory.hpp>
#include <objects/Mob.hpp>
#include <objects/actions/MovementAction.hpp>

/**
 * Configuration data
 */
struct WavePrototype {
    size_t size;
    std::vector<SpriteFactory::SpriteID> mobs;
    sf::Time preparation_time;
    sf::Time wave_time;
    sf::Time group_delay;
    size_t group_size;

    WavePrototype(std::vector<SpriteFactory::SpriteID>&& monsters, sf::Time prep_time, sf::Time max_wave_time
            , sf::Time delay_between_spawns, size_t spawns_per_group)
        : size(monsters.size()), mobs(std::move(monsters)), preparation_time(prep_time), wave_time(max_wave_time)
        , group_delay(delay_between_spawns), group_size(spawns_per_group) {};
};

class Wave {
    WavePrototype prototype_;

    const SpriteFactory *sprites_;
    World *world_;
    std::vector<Mob*> mobs_;
    sf::Time start_time_, time_since_last_group_;
    std::optional<sf::Time> finish_time_;
    std::vector<std::shared_ptr<MovementAction>> paths_;
public:
    Wave(WavePrototype prototype, World &world, const SpriteFactory &sprites, sf::Time start_time);

    void update(sf::Time delta);

    [[nodiscard]] auto getFinishTime() const -> sf::Time;
    [[nodiscard]] auto getStartTime() const -> sf::Time;
    [[nodiscard]] auto spawnedAllMobs() const -> bool;
    [[nodiscard]] auto finished() const -> bool;

protected:
    [[nodiscard]] auto _find_spawn_point_with_no_collision(SpriteFactory::SpriteID next_mob) const
        -> std::optional<sf::Vector2f>;
};


#endif //ROUGELIKE_DEV_WAVE_HPP
