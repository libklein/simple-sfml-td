//
// Created by patrick on 3/15/20.
//

#ifndef ROUGELIKE_DEV_SPRITE_HPP
#define ROUGELIKE_DEV_SPRITE_HPP


#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <fwd.hpp>
#include <nlohmann/json.hpp>
#include <TextureAtlas.hpp>
#include <memory>
#include <cmath>
#include <util/math.h>

class Location : private sf::Vector3f {
public:
    using sf::Vector3f::Vector3;
    Location(const sf::Vector3f &location);
    Location(const sf::Vector2f &position, float rotation);

    // Setters
    void setRotation(float angle);
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);

    // Getters
    [[nodiscard]] auto getRotation() const -> float;
    [[nodiscard]] auto getPosition() const -> sf::Vector2f;

    auto operator==(const Location &other) const -> bool;
    auto operator!=(const Location &other) const -> bool;
    auto operator+(const Location &other) const -> Location;
    auto operator-(const Location &other) const -> Location;
    auto operator*(float scalar) const -> Location;
    auto operator/(float scalar) const -> Location;
    auto operator+=(const Location &other) -> Location&;
    auto operator-=(const Location &other) -> Location&;
    auto operator*=(const Location &other) -> Location&;
    auto operator/=(const Location &other) -> Location&;


    auto operator+(const Velocity &velocity) const-> Location;
    auto operator+=(const Velocity &velocity) -> Location&;
};

static auto get_absolute(const Location &l) -> float {
    return std::sqrt((l.getPosition().x * l.getPosition().x) + (l.getPosition().y * l.getPosition().y));
}

static auto get_angle(const Location &l) -> float {
    return get_angle(l.getPosition().x, l.getPosition().y);
}

static auto get_distance(const Location &origin, const Location &target) -> float {
    return get_distance(origin.getPosition(), target.getPosition());
}

static auto get_angle_between(const Location &origin, const Location &target) -> float {
    return get_angle_between(origin.getPosition(), target.getPosition());
}

class Sprite : public sf::Drawable {
private:
    Location location_;

    // Rendering
    mutable sf::Transform cached_transform_ = sf::Transform::Identity;
    mutable bool transform_needs_update_ = false;

    std::array<sf::Vertex, 4> vertices_;
    const sf::Texture *texture_;

    // UUID
    std::size_t id_;
public:
    Sprite(const sf::Texture &texture, const sf::FloatRect &rectangle, size_t id);

    [[nodiscard]] virtual auto constructFromPrototype() const -> std::unique_ptr<Sprite>;

    [[nodiscard]] auto SpriteID() const -> auto { return id_; }

    [[nodiscard]] static auto FromJSON(const nlohmann::json &json, const TextureAtlas &textures) -> Sprite;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    // Setters
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);
    void setRotation(float angle);
    void setLocation(const Location &location);
    void setTextureRect(const sf::FloatRect &rect);
    void setTexture(const sf::Texture *texture);

    // Getters
    [[nodiscard]] auto getLocalBounds() const -> sf::FloatRect;
    [[nodiscard]] auto getSize() const -> sf::Vector2f;
    [[nodiscard]] auto getPosition() const -> sf::Vector2f;
    [[nodiscard]] auto getRotation() const -> float;
    [[nodiscard]] auto getLocation() const -> const Location &;

protected:
    auto _get_center() const -> sf::Vector2f;
    void _mark_dirty() const;
    void _recompute_transformation() const;
    auto _get_transform() const -> const sf::Transform&;
};

static auto get_distance(const Sprite &origin, const Sprite &target) -> float {
    return get_distance(origin.getPosition(), target.getPosition());
}

static auto get_angle_between(const Sprite &origin, const Sprite &target) -> float {
    return get_angle_between(origin.getPosition(), target.getPosition());
}


#endif //ROUGELIKE_DEV_SPRITE_HPP
