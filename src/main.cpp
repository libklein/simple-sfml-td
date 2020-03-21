#include <iostream>

#include <SFML/Graphics.hpp>
#include <world/World.hpp>
#include <filesystem>
#include <random>

/*auto randomMap(const SpriteAtlas &sprites, std::size_t x_dim, std::size_t y_dim) -> std::vector<std::vector<std::size_t>> {
    std::vector<std::vector<std::size_t>> map_data(y_dim, std::vector<size_t>(x_dim));
    auto prng = std::mt19937(rand());
    auto random = std::uniform_int_distribution<>(0, sprites.NumberOfSpritesOfKind(SpriteAtlas::TerrainSprite) - 1);
    for(auto &next_row : map_data) {
        for(auto& next_tile_id : next_row) {
            next_tile_id = random(prng);
        }
    }
    return map_data;
}*/

int main() {
    std::size_t width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "rougelike_dev");
    window.setVerticalSyncEnabled(true);

    //auto texture_atlas = std::make_shared<TextureAtlas>(TextureAtlas::LoadFromFile("./resource/Tiles/kenny/tdtiles_64.png"));
    //auto sprite_atlas = SpriteAtlas::LoadFromFile("./resource/Tiles/kenny/");

    //auto map = Map::LoadFromMemory(randomMap(sprite_atlas, width / sprite_atlas.Textures().SpriteSize(), height / sprite_atlas.Textures().SpriteSize()), sprite_atlas);
    auto [map, sprite_atlas] = Map::LoadFromFile("./resource/Maps/test.json");

    while(window.isOpen()) {
        sf::Event evt;
        while(window.pollEvent(evt)) {
            switch(evt.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                case sf::Event::Resized: {
                    window.setSize({evt.size.width, evt.size.height});
                    break;
                }
                case sf::Event::KeyReleased: {
                    if(evt.key.code == sf::Keyboard::Enter) {
                        //map = Map::LoadFromMemory(randomMap(sprite_atlas, map.Width(), map.Height()), sprite_atlas);
                    }
                }
                case sf::Event::MouseButtonReleased: {
                    if(evt.mouseButton.button == sf::Mouse::Left) {
                        auto &clicked_tile = map.getTile(evt.mouseButton.x, evt.mouseButton.y);
                        std::cout << clicked_tile.SpriteID() << std::endl;
                        //clicked_tile.build(Tile(texture_atlas, 15));
                        if(clicked_tile.canBuild()) {
                            map.addEntity(std::move(
                                    dynamic_cast<Entity &>(*sprite_atlas.CreateSprite(SpriteAtlas::StaticSprite, 0))),
                                          evt.mouseButton.x, evt.mouseButton.y);
                        } else if (clicked_tile.hasEntity()) {
                            map.removeEntity(evt.mouseButton.x, evt.mouseButton.y);
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
