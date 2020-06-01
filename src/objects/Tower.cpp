//
// Created by patrick on 3/26/20.
//

#include "Tower.hpp"
#include "Mob.hpp"
#include <world/World.hpp>

void Tower::update(sf::Time delta) {
    if(hasTarget()) {
        if(target_->isAlive()) {
            this->rotateTo(get_angle_between(*this, *target_));
        } else {
            target_ = nullptr;
        }
    }

    if(!hasTarget()) {
        target_ = _find_next_target();
    }

    for(auto &next_attack : attacks_) next_attack.update(delta);

    Unit::update(delta); // Update entity

    if(hasTarget() && _is_aimed_at_target()) {
        // Attack
        fire();
    }
}

void Tower::fire() {
    assert(hasTarget());
    for(auto &next_attack : attacks_) {
        if(next_attack.isOnCooldown()) continue;
        next_attack.trigger(target_);
    }
}

auto Tower::_is_aimed_at_target() const -> bool {
    assert(hasTarget());
    return std::abs(get_angle_between(*this, *target_) - getRotation()) <= 2;
}

void Tower::setTarget(Unit *target) {
    this->target_ = target;
}

auto Tower::hasTarget() const -> bool {
    return target_ != nullptr;
}

auto Tower::FromJSON(const nlohmann::json &data, const TextureAtlas &textures, const std::vector<Attack> &attacks) -> Tower {
    std::vector<Attack> tower_attacks;
    std::transform(data["attacks"].begin(), data["attacks"].end(), std::back_inserter(tower_attacks),
            [&attacks](size_t id) {
                return attacks[id];
            });
    return Tower(std::move(Unit::FromJSON(data, textures)), std::move(tower_attacks));
}

std::unique_ptr<Sprite> Tower::constructFromPrototype() const {
    return std::make_unique<Tower>(static_cast<const Unit&>(*this), attacks_);
}

auto Tower::_find_next_target() const -> Unit * {
    const auto &targets = getWorld()->getEntitiesInRadius(std::max_element(attacks_.begin(), attacks_.end(),
            [](const Attack &lhs, const Attack &rhs) {
                return lhs.getRange() < rhs.getRange();
            })->getRange(), this->getPosition());
    Unit *closest_target = nullptr;
    for(Entity *next_candidate : targets) {
        Mob *mob = dynamic_cast<Mob*>(next_candidate);
        if (!mob) continue;
        if(mob->isAlive() && (!closest_target || get_distance(*this, *mob) < get_distance(*this, *closest_target))) {
            closest_target = mob;
        }
    }
    return closest_target;
}

Tower::Tower(Unit &&unit, std::vector<Attack> attacks) : Unit(std::move(unit)), attacks_(std::move(attacks)) {
    assert(!attacks_.empty());
}

Tower::Tower(const Unit &unit, std::vector<Attack> attacks) : Unit(unit), attacks_(std::move(attacks)) {
    assert(!attacks_.empty());
}

Attack::Attack(sf::Time cooldown, float damagePerHit, float range)
    : cooldown_(cooldown)
    , damage_per_hit_(damagePerHit)
    , range_(range) {}

auto Attack::isOnCooldown() const -> bool {
    return time_since_last_attack_ < cooldown_;
}

auto Attack::getBaseDamage() const -> float {
    return damage_per_hit_;
}

void Attack::trigger(Unit *target) {
    assert(!isOnCooldown());
    time_since_last_attack_ = sf::Time::Zero;
    target->damage(getBaseDamage());
}

void Attack::update(sf::Time delta) {
    time_since_last_attack_ += delta;
}

auto Attack::FromJSON(const nlohmann::json &data) -> Attack {
    return Attack(sf::seconds(data["cooldown"]), data["damage"], data["range"]);
}

auto Attack::getRange() const -> float {
    return range_;
}
