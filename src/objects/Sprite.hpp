//
// Created by patrick on 3/15/20.
//

#ifndef ROUGELIKE_DEV_SPRITE_HPP
#define ROUGELIKE_DEV_SPRITE_HPP


#include <SFML/Graphics/Sprite.hpp>
#include <nlohmann/json.hpp>
#include <TextureAtlas.hpp>
#include <memory>

class Location {
protected:
    sf::Vector2f position_ = {0., 0.};
    float rotation_ = 0.;
private:
    mutable sf::Transform cached_transform_ = sf::Transform::Identity;
    mutable bool transform_needs_update_ = false;
public:
    Location() = default;
    Location(const sf::Vector2f &position, float rotation);

    // Setters
    void setRotation(float angle);
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);

    // Getters
    [[nodiscard]] auto getRotation() const -> float;
    [[nodiscard]] auto getPosition() const -> const sf::Vector2f &;

    // Computed
    [[nodiscard]] auto getTransform() const -> const sf::Transform&;

protected:
    void mark_dirty() const;
    void recompute_transformation() const;
};

class Sprite : public sf::Drawable {
protected:
    Location location_;
    std::array<sf::Vertex, 4> vertices_;
    const sf::Texture *texture_;
private:
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
    void setTextureRect(const sf::FloatRect &rect);
    void setTexture(const sf::Texture *texture);

    // Getters
    [[nodiscard]] auto getLocalBounds() const -> sf::FloatRect;
    [[nodiscard]] auto getPosition() const -> const sf::Vector2f &;

};


#endif //ROUGELIKE_DEV_SPRITE_HPP
