//
// Created by patrick on 3/13/20.
//

#ifndef ROUGELIKE_DEV_TEXTUREATLAS_HPP
#define ROUGELIKE_DEV_TEXTUREATLAS_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <filesystem>
#include <cassert>

/**
 *
 */
class TextureAtlas {
public:
    using TextureID = std::size_t;
    static constexpr TextureID NO_TEXTURE = std::numeric_limits<TextureID>::max();
protected:
    std::unique_ptr<sf::Texture> sprite_sheet_;
    size_t sprite_size_;
    TextureID sprites_per_row_, sprites_per_col_;

public:
    explicit TextureAtlas(const std::filesystem::path &path, std::size_t sprite_size);

    [[nodiscard]]
    static auto LoadFromFile(const std::filesystem::path &path) -> TextureAtlas;

    [[nodiscard]]
    auto NumberOfSprites() const -> TextureID ;

    [[nodiscard]]
    auto SpriteSize() const -> std::size_t;

    [[nodiscard]]
    auto Texture() const -> const sf::Texture&;

    template<typename T = float>
    [[nodiscard]]
    auto getTextureRect(TextureID id) const -> sf::Rect<T> {
        assert(id < NumberOfSprites());
        size_t logical_y_offset = id / sprites_per_row_;
        size_t logical_x_offset = id - logical_y_offset * sprites_per_row_;
        return sf::Rect<T>(static_cast<T>(logical_x_offset * this->sprite_size_),
                           static_cast<T>(logical_y_offset*this->sprite_size_),
                             this->sprite_size_, this->sprite_size_);
    }
};


#endif //ROUGELIKE_DEV_TEXTUREATLAS_HPP
