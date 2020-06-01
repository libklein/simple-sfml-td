//
// Created by patrick on 4/10/20.
//

#ifndef ROUGELIKE_DEV_UTILITY_HPP
#define ROUGELIKE_DEV_UTILITY_HPP

#include <vector>

namespace util {

    template<class Container>
    void unordered_remove(Container &container, typename Container::iterator position) {
        container.erase(position);
    }

    template<class T>
    void unordered_remove(std::vector<T> &container, typename std::vector<T>::iterator position) {
        std::iter_swap(std::prev(container.end()), position);
        container.pop_back();
    }

}

#endif //ROUGELIKE_DEV_UTILITY_HPP
