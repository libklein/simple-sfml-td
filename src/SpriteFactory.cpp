//
// Created by patrick on 3/15/20.
//

#include "SpriteFactory.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <objects/Tile.hpp>
#include <objects/Entity.hpp>
#include <objects/Mob.hpp>
#include <objects/Tower.hpp>

auto SpriteFactory::LoadFromFile(const std::filesystem::path &path) -> SpriteFactory {
    auto textures = TextureAtlas::LoadFromFile(path / "tdtiles_64.png");

    nlohmann::json atlas;
    {
        std::ifstream atlas_file(path / "atlas.json");
        atlas_file >> atlas;
    }

    SpriteFactory sprite_atlas(std::move(textures));
    // Read terrain sprites
    for(const auto &terrain : atlas["terrains"]) {
        for(const auto &tile : terrain) {
            sprite_atlas.add<Tile>(SpriteFactory::TerrainSprite, Tile::FromJSON(tile, sprite_atlas.Textures()));
        }
    }

    // Read attacks
    std::vector<Attack> attacks;
    std::transform(atlas["attacks"].begin(), atlas["attacks"].end(), std::back_inserter(attacks), [](const auto &data){
        return Attack::FromJSON(data);
    });

    // Read entities
    for(const auto &static_sprite : atlas["entities"]["static"]) {
        sprite_atlas.add<Entity>(SpriteFactory::StaticSprite, Entity::FromJSON(static_sprite, sprite_atlas.Textures()));
    }

    // Read entities
    for(const auto &static_sprite : atlas["entities"]["mob"]) {
        sprite_atlas.add<Mob>(SpriteFactory::EntitySprite, Mob::FromJSON(static_sprite, sprite_atlas.Textures()));
    }

    // Read entities
    for(const auto &static_sprite : atlas["entities"]["tower"]) {
        sprite_atlas.add<Tower>(SpriteFactory::EntitySprite, Tower::FromJSON(static_sprite, sprite_atlas.Textures(), attacks));
    }

    return sprite_atlas;
}

SpriteFactory::SpriteFactory(class TextureAtlas &&textures)
    : textures_(std::move(textures))
    , sprite_prototypes_(SpriteType::COUNT) {

}

auto SpriteFactory::TileSize() const -> std::size_t {
    return textures_.SpriteSize();
}

auto SpriteFactory::Textures() const -> const TextureAtlas & {
    return textures_;
}

auto SpriteFactory::NumberOfSpritesOfKind(SpriteFactory::SpriteType sprite_type) const -> std::size_t {
    return sprite_prototypes_[sprite_type].size();
}

auto SpriteFactory::getSprite(SpriteID logical_id) const -> const Sprite & {
    return *id_to_tile_[logical_id];
}

auto SpriteFactory::getSprite(SpriteID logical_id) -> Sprite & {
    return *id_to_tile_[logical_id];
}

