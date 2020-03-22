//
// Created by patrick on 3/21/20.
//

#include "Animation.hpp"
#include <algorithm>
#include <cassert>

/*auto Animation::KeyFrame::getTransform(sf::Time time_delta) const -> sf::Transform {
    assert(time_delta >= sf::Time::Zero && time_delta <= duration);
    float scale = (duration / time_delta) * speed;
    assert(scale >= 0.0 && scale <= 1.0);
    sf::Transform t;
    t.rotate(rotation_offset * scale);
    t.translate(position_offset * scale);
    return t;
}*/

auto Animation::Animation::_get_active_keyframe(sf::Time at_time) const -> animation_frames::const_iterator {
    // Negated lower_bound
    auto active_keyframe = std::lower_bound(keyframes_.begin(), keyframes_.end(), at_time,
            [](const std::pair<sf::Time, Frame> &elem, sf::Time value){
        return elem.first >= value;
    });
    return active_keyframe;
}

Animation::Animation::Animation(const TextureAtlas &textureAtlas, const std::vector<Frame> &frames)
    : textureAtlas_(&textureAtlas) {
    assert(!frames.empty());
    keyframes_.reserve(frames.size());
    sf::Time start_time;
    for(const Frame &frame : frames) {
        keyframes_.push_back(std::make_pair(start_time, frame));
        start_time += frame.duration;
    }
}

void Animation::Animation::update(sf::Time delta) {
    time_passed_ += delta;
    if(time_passed_ > getDuration() && loop_) reset();
}

void Animation::Animation::reset() {
    time_passed_ = sf::Time::Zero;
}

auto Animation::Animation::getDuration() const -> sf::Time {
    return keyframes_.back().first + keyframes_.back().second.duration;
}

auto Animation::Animation::getTexture() const -> std::pair<const sf::Texture *, sf::FloatRect> {
    if(auto active_frame = _get_active_keyframe(time_passed_); active_frame != keyframes_.end()) {
        TextureAtlas::TextureID active_texture = _get_active_keyframe(time_passed_)->second.texture;
        return std::make_pair(&textureAtlas_->Texture(), textureAtlas_->getTextureRect(active_texture));
    } else {
        return std::make_pair(&textureAtlas_->Texture(), textureAtlas_->getTextureRect(keyframes_.back().second.texture));
    }
}

/*auto Animation::Animation::getTransform() const -> sf::Transform {
    // Combine transformations when multiple frames have passed since the last update
    if(auto keyframe = _get_active_keyframe(time_passed_); keyframe != keyframes_.end()) {
        return keyframe->second.getTransform(last_delta_);
    }
    return sf::Transform::Identity;
}*/
