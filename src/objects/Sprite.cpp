//
// Created by patrick on 3/15/20.
//

#include "Sprite.hpp"
#include <objects/Unit.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

auto Sprite::constructFromPrototype() const -> std::unique_ptr<Sprite> {
    return std::make_unique<Sprite>(*this);
}

auto Sprite::FromJSON(const nlohmann::json &json, const TextureAtlas &textures) -> Sprite {
    return Sprite(textures.Texture(), textures.getTextureRect<float>(json["sprite_id"]), json["uuid"]);
}

Sprite::Sprite(const sf::Texture &texture, const sf::FloatRect &rectangle, size_t id)
    : texture_(&texture)
    , id_(id) {
    setTextureRect(rectangle);
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= _get_transform();
    states.texture = texture_;
    target.draw(vertices_.data(), 4, sf::Quads, states);
}

auto Sprite::getLocalBounds() const -> sf::FloatRect {
    float width = vertices_[1].position.x - vertices_[0].position.x;
    float height = vertices_[2].position.y - vertices_[0].position.y;
    return {0.0f, 0.0f, width, height};
}

void Sprite::setPosition(float x, float y) {
    location_.setPosition(x, y);
    _mark_dirty();
}

void Sprite::setPosition(const sf::Vector2f &position) {
    location_.setPosition(position);
    _mark_dirty();
}

void Sprite::setTexture(const sf::Texture *texture) {
    texture_ = texture;
}

auto Sprite::getPosition() const -> sf::Vector2f {
    return location_.getPosition();
}

void Sprite::setTextureRect(const sf::FloatRect &rect) {
    auto left = static_cast<float>(rect.left), width = static_cast<float>(rect.width);
    auto top = static_cast<float>(rect.top), height = static_cast<float>(rect.height);

    vertices_[0].texCoords = {left, top};
    vertices_[1].texCoords = {left + width, top};
    vertices_[2].texCoords = {left + width, top + height};
    vertices_[3].texCoords = {left, top + height};

    vertices_[0].position = {0.0, 0.0};
    vertices_[1].position = {width, 0.0};
    vertices_[2].position = {width, height};
    vertices_[3].position = {0.0, height};
}

auto Sprite::getLocation() const -> const Location & {
    return location_;
}

void Sprite::setRotation(float angle) {
    location_.setRotation(angle);
    _mark_dirty();
}

void Sprite::setLocation(const Location &location) {
    location_ = location;
    _mark_dirty();
}

auto Sprite::getRotation() const -> float {
    return getLocation().getRotation();
}

Location::Location(const sf::Vector2f &position, float rotation) : sf::Vector3f(position.x, position.y, rotation) {}

void Location::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Location::setPosition(const sf::Vector2f &pos) {
    this->x = pos.x;
    this->y = pos.y;
}

void Location::setRotation(float angle) {
    this->z = angle;
}

auto Location::getPosition() const -> sf::Vector2f {
    return {this->x, this->y};
}

auto Location::getRotation() const -> float {
    return this->z;
}

auto Location::operator+=(const Velocity &velocity) -> Location & {
    this->x += velocity.x;
    this->y += velocity.y;
    this->z += velocity.z;
    return *this;
}

auto Location::operator==(const Location &other) const -> bool {
    return static_cast<const sf::Vector3f&>(*this) == static_cast<const sf::Vector3f&>(other);
}

auto Location::operator!=(const Location &other) const -> bool {
    return static_cast<const sf::Vector3f&>(*this) != static_cast<const sf::Vector3f&>(other);
}

auto Location::operator-(const Location &other) const -> Location {
    return static_cast<const sf::Vector3f&>(*this) - static_cast<const sf::Vector3f&>(other);
}

Location::Location(const sf::Vector3f &location) : sf::Vector3f(location) {}

auto Location::operator+(const Velocity &velocity) const -> Location {
    Location l = *this;
    l += velocity;
    return l;
}

void Sprite::_mark_dirty() const {
    transform_needs_update_ = true;
}

void Sprite::_recompute_transformation() const {
    cached_transform_ = sf::Transform::Identity;
    cached_transform_.translate(getPosition()).rotate(getRotation(), _get_center());
    transform_needs_update_ = false;
}

auto Sprite::_get_transform() const -> const sf::Transform & {
    if(transform_needs_update_) _recompute_transformation();
    return cached_transform_;
}

auto Sprite::_get_center() const -> sf::Vector2f {
    return {getLocalBounds().width / 2.0f, getLocalBounds().height / 2.0f};
}

auto Sprite::getSize() const -> sf::Vector2f {
    return sf::Vector2f(getLocalBounds().width, getLocalBounds().height);
}
