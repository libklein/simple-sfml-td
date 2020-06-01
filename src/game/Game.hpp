//
// Created by patrick on 3/21/20.
//

#ifndef ROUGELIKE_DEV_GAME_HPP
#define ROUGELIKE_DEV_GAME_HPP

#include <world/World.hpp>
#include <game/Wave.hpp>

/**
 * Instance of a game played.
 */
class Game {
    const SpriteFactory *sprites_;
    /// The game world - contains all entities
    World world_;

    /// Waves
    std::vector<WavePrototype> waves_;
    /// Active waves
    std::vector<Wave> active_waves_;
    /// Finished waves
    std::vector<Wave> finished_waves_;

    /// Time passed
    sf::Clock game_timer_;
    /// Wave counter
    size_t wave_counter_ = 0;
    /// Lifes
    size_t lifes_remaining_;
    /// Game AI
    // TODO - Add AI

    /// Players?

public:
    Game(const SpriteFactory &sprites, World &&world, std::vector<WavePrototype> &&waves, size_t lifes = 50);

    void start();

    void update(sf::Time delta);

    [[nodiscard]] auto getTimeToNextWave() const -> sf::Time;
    [[nodiscard]] auto isWaveActive() const -> bool;
    [[nodiscard]] auto getLifes() const -> size_t;
    [[nodiscard]] auto getWaveCount() const -> size_t;
    [[nodiscard]] auto isGameOver() const -> bool;
    [[nodiscard]] auto getWorld() const -> const World&;

    [[nodiscard]] auto getWorld() -> World&;
protected:
    void spawn_next_wave();
    [[nodiscard]] auto nextWave() const -> const WavePrototype&;

    void endGame();
};


#endif //ROUGELIKE_DEV_GAME_HPP
