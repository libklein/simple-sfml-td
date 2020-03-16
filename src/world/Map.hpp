//
// Created by patrick on 3/14/20.
//

#ifndef ROUGELIKE_DEV_MAP_HPP
#define ROUGELIKE_DEV_MAP_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <objects/Tile.hpp>
#include <SpriteAtlas.hpp>
#include <filesystem>
#include <vector>

class Map : public sf::Drawable {
    std::vector<Tile> tiles_;
    std::size_t x_size_, y_size_, tile_size_;
public:
    Map(std::size_t x, std::size_t y, const Tile &default_tile);

    static auto LoadFromFile(const std::filesystem::path &path) -> std::pair<Map, SpriteAtlas>;
    static auto LoadFromMemory(const std::vector<std::pair<std::pair<size_t, size_t>, SpriteAtlas::SpriteID>> &,
            const SpriteAtlas&,
            const Tile &default_tile,
            size_t size_x, size_t size_y) -> Map;

    [[nodiscard]] auto Width() const -> std::size_t;
    [[nodiscard]] auto Height() const -> std::size_t;

    [[nodiscard]] auto getTile(float x, float y) const -> const Tile&;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    auto set_tile(std::size_t offset, Tile&& tile) -> Tile&;
    [[nodiscard]] auto get_offset(std::size_t x, std::size_t y) const -> std::size_t;
    [[nodiscard]] auto get_logical_coord(std::size_t offset) const -> std::pair<std::size_t, std::size_t>;
};


#endif //ROUGELIKE_DEV_MAP_HPP
