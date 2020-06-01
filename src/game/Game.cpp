//
// Created by patrick on 3/21/20.
//

#include <iostream>
#include "Game.hpp"

void Game::start() {
    game_timer_.restart();
}

void Game::update(sf::Time delta) {
    bool finished_game_earlier = isGameOver();
    world_.update(delta);

    // Move finished waves into finished_waves_
    for(auto next_active_wave = active_waves_.begin(); next_active_wave != active_waves_.end();) {
        if(next_active_wave->finished()) {
            finished_waves_.push_back(std::move(*next_active_wave));
            next_active_wave = active_waves_.erase(next_active_wave);
        } else {
            ++next_active_wave;
        }
    }

    for(auto &wave : active_waves_) {
        wave.update(delta);
    }

    if(isGameOver()) {
        if(!finished_game_earlier) {
            this->endGame();
        }
        return;
    }

    // Should we spawn the next wave?
    if(getTimeToNextWave() <= sf::Time::Zero) {
        spawn_next_wave();
        assert(getTimeToNextWave() >= sf::Time::Zero - sf::seconds(1));
    }
}

auto Game::getTimeToNextWave() const -> sf::Time {
    if(active_waves_.empty()) {
        if(finished_waves_.empty()) {
            return nextWave().preparation_time - game_timer_.getElapsedTime();
        } else {
            return nextWave().preparation_time - (game_timer_.getElapsedTime() - finished_waves_.back().getFinishTime());
        }
    } else {
        return nextWave().preparation_time - (game_timer_.getElapsedTime() - active_waves_.back().getStartTime());
    }
}

auto Game::isWaveActive() const -> bool {
    return false;
}

auto Game::getLifes() const -> size_t {
    return lifes_remaining_;
}

auto Game::getWaveCount() const -> size_t {
    return wave_counter_;
}

auto Game::isGameOver() const -> bool {
    return (wave_counter_ == waves_.size() && active_waves_.empty()) || getLifes() == 0;
}

void Game::spawn_next_wave() {
    active_waves_.emplace_back(nextWave(), world_, *sprites_, game_timer_.getElapsedTime());
    ++wave_counter_;
}

auto Game::nextWave() const -> const WavePrototype & {
    assert(!isGameOver());
    return waves_[getWaveCount()];
}

Game::Game(const SpriteFactory &sprites, World &&world, std::vector<WavePrototype> &&waves, size_t lifes)
: sprites_(&sprites), world_(std::move(world)), waves_(std::move(waves)), lifes_remaining_(lifes) {

}

auto Game::getWorld() const -> const World & {
    return world_;
}

void Game::endGame() {
    std::cout << "Game has been won!" << std::endl;
}

auto Game::getWorld() -> World & {
    return world_;
}
