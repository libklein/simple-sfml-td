//
// Created by patrick on 3/14/20.
//

#include "Map.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(const auto & tile : tiles_) {
        target.draw(tile, states);
    }
    auto beg = static_entities_.begin();
    auto end = static_entities_.end();
    for(const auto & entity : static_entities_) {
        target.draw(entity, states);
    }
}

Map::Map(std::size_t x, std::size_t y, const Tile &default_tile)
    : tiles_(x*y, default_tile), x_size_(x), y_size_(y), tile_size_(default_tile.getLocalBounds().width)
    , static_entities_(tiles_.size())
{
    assert(default_tile.getLocalBounds().width == default_tile.getLocalBounds().height);
    for(size_t i = 0; i < x; ++i) {
        for(size_t j = 0; j < y; ++j) {
            tiles_[get_offset({i,j})].setPosition(i*tile_size_, j*tile_size_);
        }
    }
}

auto Map::get_offset(std::pair<std::size_t, std::size_t> grid_coords) const -> std::size_t {
    assert(grid_coords.first <= x_size_ && grid_coords.second <= y_size_);
    return grid_coords.second * x_size_ + grid_coords.first;
}

auto Map::LoadFromMemory(const std::vector<std::pair<std::pair<size_t, size_t>, SpriteAtlas::SpriteID>> &data, const SpriteAtlas &sprites,
                         const Tile &default_tile, size_t size_x, size_t size_y) -> Map {
    Map map(size_x, size_y, default_tile);

    for(const auto [coords, id]: data) {
        auto tile = std::move(dynamic_cast<Tile&>(*sprites.CreateSprite(SpriteAtlas::TerrainSprite, id)));
        map.set_tile(map.get_offset(coords), std::move(tile));
    }

    return std::move(map);
}

auto Map::LoadFromFile(const std::filesystem::path &path) -> std::pair<Map, SpriteAtlas> {
    nlohmann::json map_data;
    {
        std::ifstream map_stream(path);
        map_stream >> map_data;
    }
    // Load sprite atlas
    auto sprites = SpriteAtlas::LoadFromFile(std::filesystem::path("resource/Tiles") / map_data["tileset"]);
    auto create_tile = [&sprites] (SpriteAtlas::SpriteID id) -> Tile&& {
        return std::move(dynamic_cast<Tile&>(*sprites.CreateSprite(SpriteAtlas::TerrainSprite, id)));
    };

    // Initialize with default tile
    Tile default_tile = create_tile(map_data["default-tile"]);
    Map map(map_data["dimension"][0], map_data["dimension"][1], default_tile);

    for(const auto &tile : map_data["tiles"]) {
        map.set_tile(map.get_offset({tile["x"], tile["y"]}), create_tile(tile["tile_id"]));
    }

    return {std::move(map), std::move(sprites)};
}

auto Map::Height() const -> std::size_t {
    return y_size_;
}

auto Map::Width() const -> std::size_t {
    return x_size_;
}

auto Map::get_logical_coord(std::size_t offset) const -> std::pair<std::size_t, std::size_t> {
    assert(offset < tiles_.size());
    auto y_offset = offset / x_size_;
    return {offset - (y_offset * x_size_), y_offset};
}

auto Map::getTile(float x, float y) const -> const Tile & {
    return tiles_[this->get_offset(translate_to_grid(x, y))];
}

auto Map::set_tile(std::size_t offset, Tile &&tile) -> Tile & {
    auto pos = tiles_[offset].getPosition();
    tiles_[offset] = std::move(tile);
    tiles_[offset].setPosition(pos);
    return tiles_[offset];
}

auto Map::addEntity(Entity &&entity, float x, float y) -> Entity & {
    auto top_left_offset = get_offset(translate_to_grid(x, y));
    Tile &tile = tiles_[top_left_offset];
    assert(tile.canBuild());
    // TODO Remove entity

    Entity &local_entity = static_entities_.insert(std::move(entity));

    tile.setEntity(&local_entity);
    local_entity.setPosition(tile.getPosition());
    return local_entity;
}

auto Map::translate_to_grid(float x, float y) const -> std::pair<std::size_t, std::size_t> {
    return {static_cast<size_t>(x / tile_size_), static_cast<size_t>(y / tile_size_)};
}

void Map::removeEntity(float x, float y) {
    auto top_left_offset = get_offset(translate_to_grid(x, y));
    Tile &tile = tiles_[top_left_offset];

    assert(tile.hasEntity());
    static_entities_.remove(tile.releaseEntity());
}


