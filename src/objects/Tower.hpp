//
// Created by patrick on 3/26/20.
//

#ifndef ROUGELIKE_DEV_TOWER_HPP
#define ROUGELIKE_DEV_TOWER_HPP

#include <objects/Unit.hpp>

class Attack {
    /// Cooldown in seconds
    sf::Time cooldown_;
    /// Damage
    float damage_per_hit_;
    /// Attack Range
    float range_;
    /// Time that has passed since the last attack
    sf::Time time_since_last_attack_ = sf::Time::Zero;

public:
    Attack(sf::Time cooldown, float damagePerHit, float range);

    [[nodiscard]] auto isOnCooldown() const -> bool;
    [[nodiscard]] auto getBaseDamage() const -> float;
    [[nodiscard]] auto getRange() const -> float;

    /// Triggers the attack, attacking target
    void trigger(Unit *target);

    void update(sf::Time delta);


    static auto FromJSON(const nlohmann::json &data) -> Attack;
};

class Tower : public Unit {
private:
    /// Attacks
    std::vector<Attack> attacks_;
    /// Current target
    Unit *target_ = nullptr;

    [[nodiscard]] auto _is_aimed_at_target() const -> bool;

protected:
    void fire();

    [[nodiscard]] auto _find_next_target() const -> Unit*;
public:
    Tower(Unit &&unit, std::vector<Attack> attacks);
    Tower(const Unit &unit, std::vector<Attack> attacks);

    void update(sf::Time delta) override;

    void setTarget(Unit *target);
    [[nodiscard]] auto hasTarget() const -> bool;


    static auto FromJSON(const nlohmann::json &data, const TextureAtlas &textures, const std::vector<Attack> &attacks)
        -> Tower;
    std::unique_ptr<Sprite> constructFromPrototype() const override;
};


#endif //ROUGELIKE_DEV_TOWER_HPP
