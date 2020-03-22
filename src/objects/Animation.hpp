//
// Created by patrick on 3/21/20.
//

#ifndef ROUGELIKE_DEV_ANIMATION_HPP
#define ROUGELIKE_DEV_ANIMATION_HPP

#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>
#include <TextureAtlas.hpp>

namespace Animation {

    /*struct KeyFrame {
        float rotation_offset = 0.0;
        sf::Vector2f position_offset = {0.0, 0.0};
        sf::Time duration = sf::Time::Zero;

        /// scales time passed linearly
        float speed = 1.0;
        [[nodiscard]] auto getTransform(sf::Time time_delta) const -> sf::Transform;
    };*/

    struct Frame {
        TextureAtlas::TextureID texture = TextureAtlas::NO_TEXTURE;
        sf::Time duration = sf::Time::Zero;
    };

    /**
     * Does not change an Entity's location.
     */
    class Animation {
    public:
    protected:
        /// Vector of pairs, each containing a key frame and it's offset in the animation
        using animation_frames = std::vector<std::pair<sf::Time, Frame>>;
        /// The used texture atlas
        const TextureAtlas *textureAtlas_;
        /// The animation's keyframes
        animation_frames keyframes_;
        /// Should the animation loop?
        bool loop_ = false;
        /// Current time in the animation
        sf::Time time_passed_ = sf::Time::Zero;

    public:
        explicit Animation(const TextureAtlas &textureAtlas, const std::vector<Frame> &frames);

        void update(sf::Time delta);

        /**
         * Reset the animation.
         */
        void reset();

        // Getters
        [[nodiscard]] auto getDuration() const -> sf::Time;

        // Computed
        [[nodiscard]] auto getTexture() const -> std::pair<const sf::Texture*, sf::FloatRect>;

    protected:
        [[nodiscard]] auto _get_active_keyframe(sf::Time at_time) const -> animation_frames::const_iterator;
    };
}

#endif //ROUGELIKE_DEV_ANIMATION_HPP
