//
// Created by patrick on 3/26/20.
//

#ifndef ROUGELIKE_DEV_UNIT_HPP
#define ROUGELIKE_DEV_UNIT_HPP

#include <SFML/System/Vector3.hpp>
#include <objects/Entity.hpp>
#include <objects/actions/Action.hpp>
#include <ostream>
#include <optional>

struct Velocity : public sf::Vector3f {
    /// x and y indicate the velocity in x and y direction (in units per second)
    /// z indicates the rotation speed (in degree per second)

    using sf::Vector3f::Vector3f;

    [[nodiscard]] auto getAbsolute() const -> float {
        return std::sqrt(x*x + y*y);
    }

    [[nodiscard]] auto getTurnSpeed() const -> float {
        return z;
    }

    friend std::ostream &operator<<(std::ostream &os, const Velocity &velocity);

    auto operator*(sf::Time seconds) const -> Velocity;
    auto operator*=(sf::Time seconds) -> Velocity&;
};

static auto get_absolute(const Velocity &l) -> float {
    return l.getAbsolute();
}

static auto get_angle(const Velocity &l) -> float {
    return get_angle({l.x, l.y});
}

class Unit : public Entity {
    Velocity velocity_ = {};

    std::optional<Location> target_;

    float max_speed_, max_turn_speed_;
    float max_health_, health_;

    std::shared_ptr<Action> action_ = nullptr;
public:
    Unit(Entity&& entity, float max_speed, float max_turn_speed, float max_health);
    Unit(const Entity& entity, float max_speed, float max_turn_speed, float max_health);

    std::unique_ptr<Sprite> constructFromPrototype() const override;
    static auto FromJSON(const nlohmann::json &data, const TextureAtlas &textures) -> Unit;

    void update(sf::Time delta) override;

    void setHealth(float health);
    void damage(float damage); /// Modify damage

    [[nodiscard]] auto isAlive() const -> bool override;

    void setAction(std::shared_ptr<Action> action);

    void setVelocity(Velocity v);
    void stop();
    void rotateTo(float angle);
    void moveTo(sf::Vector2f position);
    void moveTo(Location position);

    /// TODO On killed listener?

};


#endif //ROUGELIKE_DEV_UNIT_HPP
