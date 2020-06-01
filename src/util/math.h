//
// Created by patrick on 3/29/20.
//

#ifndef ROUGELIKE_DEV_MATH_H
#define ROUGELIKE_DEV_MATH_H

#include <fwd.hpp>
#include <cmath>
#include <SFML/System.hpp>

// TODO Once math functions are constexpr, replace by std::atan2(0, -1) * 4;
static constexpr float PI = 3.141592653589793238462643383279502884e+00;

static auto get_absolute(float x, float y) -> float {
    return std::sqrt(x*x + y*y);
}

static auto get_absolute(const sf::Vector2f &vec) -> float {
    return std::sqrt(vec.x*vec.x + vec.y*vec.y);
}

static auto get_angle(float x, float y) -> float {
    return atan2f(y, x) * 180.0f / PI;
}

static auto get_angle(const sf::Vector2f &vec) -> float {
    return get_angle(vec.x, vec.y);
}

static auto get_distance(const sf::Vector2f &origin, const sf::Vector2f &target) -> float {
    return get_absolute(target - origin);
}

static auto get_angle_between(const sf::Vector2f &origin, const sf::Vector2f &target) -> float {
    return get_angle(target - origin);
}

template<class T>
static auto sgn(T t) -> T {
    static_assert(std::is_arithmetic_v<T>);
    return (t <= static_cast<T>(0)) ? static_cast<T>(-1) : static_cast<T>(1);
}

namespace util {
}

#endif //ROUGELIKE_DEV_MATH_H
