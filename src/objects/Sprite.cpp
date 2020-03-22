//
// Created by patrick on 3/15/20.
//

#include "Sprite.hpp"
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
    states.transform *= location_.getTransform();
    states.texture = texture_;
    target.draw(vertices_.data(), 4, sf::Quads, states);
}

auto Sprite::getLocalBounds() const -> sf::FloatRect {
    float width = vertices_[1].position.x - vertices_[0].position.x;
    float height = vertices_[2].position.y - vertices_[0].position.y;
    return {0.0, 0.0, width, height};
}

void Sprite::setPosition(float x, float y) {
    location_.setPosition(x, y);
}

void Sprite::setPosition(const sf::Vector2f &position) {
    location_.setPosition(position);
}

void Sprite::setTexture(const sf::Texture *texture) {
    texture_ = texture;
}

auto Sprite::getPosition() const -> const sf::Vector2f & {
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

Location::Location(const sf::Vector2f &position, float rotation) : position_(position), rotation_(rotation) {}

void Location::setPosition(float x, float y) {
    position_ = {x, y};
    mark_dirty();
}

void Location::setPosition(const sf::Vector2f &pos) {
    position_ = pos;
    mark_dirty();
}

void Location::setRotation(float angle) {
    rotation_ = angle;
    mark_dirty();
}

auto Location::getPosition() const -> const sf::Vector2f & {
    return position_;
}

auto Location::getTransform() const -> const sf::Transform & {
    if(transform_needs_update_) recompute_transformation();
    return cached_transform_;
}

void Location::mark_dirty() const {
    transform_needs_update_ = true;
}

void Location::recompute_transformation() const {
    cached_transform_ = sf::Transform::Identity;
    cached_transform_.translate(getPosition()).rotate(getRotation());
    transform_needs_update_ = false;
}

auto Location::getRotation() const -> float {
    return rotation_;
}
