//
// Created by patrick on 3/26/20.
//

#include <iostream>
#include "Unit.hpp"

std::unique_ptr<Sprite> Unit::constructFromPrototype() const {
    return std::make_unique<Unit>(*this);
}

void Unit::update(sf::Time delta) {
    if(action_) {
        if(action_->execute(*this)) {
            action_.reset();
        }
    }
    // Calculate velocity
    if(target_) {
        auto movement_vector = *target_ - getLocation();
        auto next_location = getLocation();
        if(getPosition() != target_->getPosition()) {
            if(float angle = get_angle(movement_vector); getRotation() != get_angle(movement_vector)) {
                // Case 1: Rotate towards direction of movement
                float dr = std::min(max_turn_speed_ * delta.asSeconds(), std::abs(angle - getRotation()));
                next_location.setRotation(next_location.getRotation() + sgn(angle - getRotation()) * dr);
            } else {
                // Case 2: Move towards target
                sf::Vector2f direction = movement_vector.getPosition() / get_absolute(movement_vector);
                float dx = std::min(max_speed_ * delta.asSeconds() * std::abs(direction.x), std::abs(movement_vector.getPosition().x));
                float dy = std::min(max_speed_ * delta.asSeconds() * std::abs(direction.y), std::abs(movement_vector.getPosition().y));
                direction.x *= dx;
                direction.y *= dy;
                next_location.setPosition(next_location.getPosition() + direction);
            }
        } else if(getRotation() != target_->getRotation()) {
            // Case 3: Rotate towards direction
            float dr = std::min(max_turn_speed_ * delta.asSeconds(), std::abs(target_->getRotation() - getRotation()));
            next_location.setRotation(next_location.getRotation() + sgn(target_->getRotation() - getRotation()) * dr);
        }
        this->setLocation(next_location);
    }
}

auto Unit::FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Unit {
    return Unit(std::move(Entity::FromJSON(data, textures)),
            data["speed"], data["turn_speed"], data["health"]);
}

Unit::Unit(const Entity &entity, float max_speed, float max_turn_speed, float max_health)
    : Entity(entity), max_speed_(max_speed), max_turn_speed_(max_turn_speed)
    , max_health_(max_health), health_(max_health_) {}

Unit::Unit(Entity&& entity, float max_speed, float max_turn_speed, float max_health)
        : Entity(std::move(entity)), max_speed_(max_speed), max_turn_speed_(max_turn_speed)
        , max_health_(max_health), health_(max_health_) {}

void Unit::setVelocity(Velocity v) {
    velocity_ = v;
    // Ensure velocity is respected
    if(velocity_.getAbsolute() > max_speed_) {
        float scale = max_speed_ / velocity_.getAbsolute();
        velocity_.x *= scale;
        velocity_.y *= scale;
    }
    if(velocity_.getTurnSpeed() > max_turn_speed_) {
        velocity_.z = max_speed_;
    }
    std::cout << "Set velocity to " << velocity_ << std::endl;
}

void Unit::setAction(std::shared_ptr<Action> action) {
    action_ = std::move(action);
}

void Unit::stop() {
    this->target_.reset();
}

void Unit::rotateTo(float angle) {
    target_ = Location(getPosition(), angle);
}

void Unit::moveTo(sf::Vector2f position) {
    float target_angle = get_angle(position - getLocation().getPosition());
    target_ = Location(position, target_angle);
}

void Unit::moveTo(Location position) {
    target_ = position;
}

auto Velocity::operator*(sf::Time seconds) const -> Velocity {
    return Velocity(this->x * seconds.asSeconds(), this->y * seconds.asSeconds(), this->z * seconds.asSeconds());
}

auto Velocity::operator*=(sf::Time seconds) -> Velocity & {
    return static_cast<Velocity&>(*this *= seconds.asSeconds());
}

std::ostream &operator<<(std::ostream &os, const Velocity &velocity) {
    os << "[" << velocity.x << ", " << velocity.y << ", " << velocity.z << "]";
    return os;
}
