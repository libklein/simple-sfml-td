#include <iostream>

#include <SFML/Graphics.hpp>
#include <world/World.hpp>
#include <filesystem>
#include <random>
#include <objects/Unit.hpp>
#include <objects/Mob.hpp>
#include <objects/actions/MovementAction.hpp>
#include <game/Game.hpp>

int main() {
    std::size_t width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "rougelike_dev");
    window.setVerticalSyncEnabled(true);


    auto [game, sprite_factory] = [](){
        auto [map, _sprite_factory] = Map::LoadFromFile("./resource/Maps/test.json");
        std::unique_ptr<SpriteFactory> sprite_factory = std::make_unique<SpriteFactory>(std::move(_sprite_factory));
        auto world = World(std::move(map), *sprite_factory);

        std::vector<WavePrototype> waves = {{{12, 12},
                                                    sf::seconds(2),
                                                    sf::seconds(60),
                                                    sf::seconds(2),
                                                    2}};
        return std::make_tuple(Game(*sprite_factory, std::move(world), std::move(waves), 50), std::move(sprite_factory));
    }();

    sf::Clock clock;
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
                    /*if(evt.key.code == sf::Keyboard::Enter) {
                        auto enemy = sprite_factory.CreateEntity<Mob>(12);
                        auto coord = world.getMap().getSpawnPoints().front()->getPosition();
                        auto &unit = dynamic_cast<Mob&>(world.spawn(std::move(enemy), coord.x, coord.y));

                        auto target_coord = world.getMap().getTargets().front()->getPosition();
                        auto action = std::make_shared<MovementAction>(target_coord);

                        unit.setAction(action);
                    }*/
                }
                case sf::Event::MouseButtonReleased: {
                    if(evt.mouseButton.button == sf::Mouse::Left) {
                        auto &world = game.getWorld();
                        auto &clicked_tile = world.getMap().getTile(evt.mouseButton.x, evt.mouseButton.y);
                        std::cout << clicked_tile.SpriteID() << std::endl;
                        if(clicked_tile.isBuildable()) {
                            if (clicked_tile.canBuild()) {
                                world.spawn<Tower>(13, evt.mouseButton.x, evt.mouseButton.y);
                            } else if (clicked_tile.hasEntity()) {
                                world.removeFromWorld(clicked_tile.getEntity());
                            }
                        }
                    }
                }
            }
        }

        // Update the world
        game.update(clock.getElapsedTime());
        clock.restart();

        // Draw it
        window.clear();
        window.draw(game.getWorld());
        window.display();
    }

    return 0;
}
