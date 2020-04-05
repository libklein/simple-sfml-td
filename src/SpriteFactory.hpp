//
// Created by patrick on 3/15/20.
//

#ifndef ROUGELIKE_DEV_SPRITEFACTORY_HPP
#define ROUGELIKE_DEV_SPRITEFACTORY_HPP

#include <TextureAtlas.hpp>
#include <objects/Sprite.hpp>
#include <memory>

class SpriteFactory {
public:
    enum SpriteType {
        TerrainSprite = 0, EntitySprite = 1, EffectSprite = 2, StaticSprite = 3, COUNT = 4
    };
    using SpriteID = size_t;
private:
    TextureAtlas textures_;

    std::vector<std::vector<std::unique_ptr<Sprite>>> sprite_prototypes_;

    std::vector<Sprite*> id_to_tile_;
public:
    explicit SpriteFactory(TextureAtlas &&);

    static auto LoadFromFile(const std::filesystem::path &) -> SpriteFactory;

    [[nodiscard]] auto TileSize() const -> std::size_t;
    [[nodiscard]] auto Textures() const -> const TextureAtlas&;
    [[nodiscard]] auto NumberOfSpritesOfKind(SpriteType) const -> std::size_t;

    template<class Object>
    [[nodiscard]] auto CreateEntity(SpriteID sprite_id) const -> std::unique_ptr<Object> {
        std::unique_ptr<Sprite> ptr = getSprite(sprite_id).constructFromPrototype();
        auto &obj = dynamic_cast<Object&>(*ptr); // Will throw on failure to cast
        ptr.release();
        return std::unique_ptr<Object>(&obj);
    }

    /*
    template<class Object>
    [[nodiscard]] auto CreateEntity(SpriteType sprite_type, size_t sprite_id) const -> std::unique_ptr<Object> {
        std::unique_ptr<Sprite> ptr = sprite_prototypes_[sprite_type][sprite_id]->constructFromPrototype();
        auto &obj = dynamic_cast<Object&>(*ptr); // Will throw on failure to cast
        ptr.release();
        return std::unique_ptr<Object>(&obj);
    }*/

    template<class T>
    auto add(SpriteType sprite_type, T&& tile) -> T& {
        sprite_prototypes_[sprite_type].push_back(std::make_unique<T>(std::forward<T>(tile)));
        id_to_tile_.emplace_back(sprite_prototypes_[sprite_type].back().get());
        return static_cast<T&>(*sprite_prototypes_[sprite_type].back());
    }

    [[nodiscard]] auto getSprite(SpriteID logical_id) const -> const Sprite&;
    [[nodiscard]] auto getSprite(SpriteID logical_id) -> Sprite&;
};


#endif //ROUGELIKE_DEV_SPRITEFACTORY_HPP
