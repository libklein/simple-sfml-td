//
// Created by patrick on 3/14/20.
//

#ifndef ROUGELIKE_DEV_MAP_HPP
#define ROUGELIKE_DEV_MAP_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <objects/Tile.hpp>
#include <objects/Entity.hpp>
#include <SpriteAtlas.hpp>
#include <filesystem>
#include <vector>
#include <util/pool.hpp>

class Map : public sf::Drawable {
    std::vector<Tile> tiles_;
    std::size_t x_size_, y_size_, tile_size_;

    util::iterable_pool<Entity> static_entities_;

    std::vector<const Tile*> spawns_;
    std::vector<const Tile*> targets_;
public:
    Map(std::size_t x, std::size_t y, const Tile &default_tile);
    Map(const Map &other) = delete;
    Map& operator=(const Map &other) = delete;
    Map(Map &&other) noexcept = default;
    Map& operator=(Map &&other) noexcept = default;

    static auto LoadFromFile(const std::filesystem::path &path) -> std::pair<Map, SpriteAtlas>;
    static auto LoadFromMemory(const std::vector<std::pair<std::pair<size_t, size_t>, SpriteAtlas::SpriteID>> &,
            const SpriteAtlas&,
            const Tile &default_tile,
            size_t size_x, size_t size_y) -> Map;

    [[nodiscard]] auto Width() const -> std::size_t;
    [[nodiscard]] auto Height() const -> std::size_t;

    [[nodiscard]] auto getTile(float x, float y) const -> const Tile&;
    [[nodiscard]] auto getSpawnPoints() const -> const std::vector<const Tile*>&;
    [[nodiscard]] auto getTargets() const -> const std::vector<const Tile*>&;

    /**
     * Add an entity to all tiles covered by it
     * @param entity
     * @param x
     * @param y
     * @return
     */
    auto addEntity(Entity &&entity, float x, float y) -> Entity&;

    /**
     * Remove the entity at position (x,y) from the map.
     * Also clears all respective tiles
     * @param x
     * @param y
     */
    void removeEntity(float x, float y);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    [[nodiscard]] auto _get_tile(size_t x, size_t y) -> Tile&;
    auto set_tile(std::size_t offset, Tile&& tile) -> Tile&;
    [[nodiscard]] auto get_offset(std::pair<std::size_t, std::size_t> grid_coords) const -> std::size_t;
    [[nodiscard]] auto translate_to_grid(float x, float y) const -> std::pair<std::size_t, std::size_t>;
    [[nodiscard]] auto get_logical_coord(std::size_t offset) const -> std::pair<std::size_t, std::size_t>;
};


#endif //ROUGELIKE_DEV_MAP_HPP
