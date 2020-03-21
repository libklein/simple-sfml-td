//
// Created by patrick on 3/15/20.
//

#include "SpriteAtlas.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <objects/Tile.hpp>
#include <objects/Entity.hpp>

auto SpriteAtlas::LoadFromFile(const std::filesystem::path &path) -> SpriteAtlas {
    auto textures = TextureAtlas::LoadFromFile(path / "tdtiles_64.png");

    nlohmann::json atlas;
    {
        std::ifstream atlas_file(path / "atlas.json");
        atlas_file >> atlas;
    }

    SpriteAtlas sprite_atlas(std::move(textures));
    // Read terrain sprites
    for(const auto &terrain : atlas["terrains"]) {
        for(const auto &tile : terrain) {
            sprite_atlas.add<Tile>(SpriteAtlas::TerrainSprite, Tile::FromJSON(tile, sprite_atlas.Textures()));
        }
    }
    // Read entities
    for(const auto &static_sprite : atlas["entities"]["static"]) {
        sprite_atlas.add<Entity>(SpriteAtlas::StaticSprite, Entity::FromJSON(static_sprite, sprite_atlas.Textures()));
    }

    return sprite_atlas;
}

SpriteAtlas::SpriteAtlas(class TextureAtlas &&textures)
    : textures_(std::move(textures))
    , sprite_prototypes_(SpriteType::COUNT) {

}

auto SpriteAtlas::CreateSprite(size_t tile_id) const -> std::unique_ptr<Sprite> {
    return getSprite(tile_id).constructFromPrototype();
}

auto SpriteAtlas::CreateSprite(SpriteAtlas::SpriteType sprite_type, size_t tile_id) const -> std::unique_ptr<Sprite> {
    return sprite_prototypes_[sprite_type][tile_id]->constructFromPrototype();
}

auto SpriteAtlas::TileSize() const -> std::size_t {
    return textures_.SpriteSize();
}

auto SpriteAtlas::Textures() const -> const TextureAtlas & {
    return textures_;
}

auto SpriteAtlas::NumberOfSpritesOfKind(SpriteAtlas::SpriteType sprite_type) const -> std::size_t {
    return sprite_prototypes_[sprite_type].size();
}

auto SpriteAtlas::getSprite(SpriteID logical_id) const -> const Sprite & {
    return *id_to_tile_[logical_id];
}

auto SpriteAtlas::getSprite(SpriteID logical_id) -> Sprite & {
    return *id_to_tile_[logical_id];
}

