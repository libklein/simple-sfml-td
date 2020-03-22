//
// Created by patrick on 3/13/20.
//

#include "TextureAtlas.hpp"
#include <cassert>

auto TextureAtlas::LoadFromFile(const std::filesystem::path &path) -> TextureAtlas {
    // Files are formatted <name>_<size>.something
    std::string_view filename = path.filename().string();
    auto begin = filename.rfind("_");
    if(begin == std::string_view::npos) {
        throw std::runtime_error("Could not parse filename!");
    }
    auto end = filename.find('.', begin);
    if(end == std::string_view::npos) {
        throw std::runtime_error("Could not parse filename!");
    }
    std::size_t sprite_size = std::stoi(filename.substr(begin+1, end).data());
    return TextureAtlas(path, sprite_size);
}

TextureAtlas::TextureAtlas(const std::filesystem::path &path, std::size_t sprite_size) : sprite_sheet_(std::make_unique<sf::Texture>()), sprite_size_(sprite_size) {
    if(!sprite_sheet_->loadFromFile(path.string())) {
        throw std::runtime_error("Could not load sprite sheet!");
    }
    if(this->sprite_sheet_->getSize().x % this->sprite_size_ != 0 || this->sprite_sheet_->getSize().y % this->sprite_size_ != 0) {
        throw std::runtime_error("Sprite sheet has invalid dimensions!");
    }
    sprites_per_row_ = this->sprite_sheet_->getSize().x / this->sprite_size_;
    sprites_per_col_ = this->sprite_sheet_->getSize().y / this->sprite_size_;
}

auto TextureAtlas::Texture() const -> const sf::Texture& {
    return *sprite_sheet_;
}

auto TextureAtlas::NumberOfSprites() const -> TextureID {
    return sprites_per_row_ * sprites_per_col_;
}

auto TextureAtlas::SpriteSize() const -> std::size_t {
    return sprite_size_;
}
