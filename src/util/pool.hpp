//
// Created by patrick on 3/20/20.
//

#ifndef ROUGELIKE_DEV_POOL_HPP
#define ROUGELIKE_DEV_POOL_HPP

#include <variant>
#include <vector>
#include <cassert>
#include <type_traits>
#include <dynamic_bitset/dynamic_bitset.hpp>

namespace util {
    template<class T>
    class pool {
    protected:
        union element_type;
        union element_type {
            element_type *next_free;
            T value;
        };
    private:
        using storage_type = std::vector<element_type>;
    public:
        using size_type = typename storage_type::size_type;

        std::vector<element_type> pool_;
        element_type *first_free_;
        size_type size_;
    public:
        explicit pool(size_type size) : pool_(size), first_free_(nullptr), size_(0) {
            auto prev_element_iter = pool_.rbegin();
            for (auto element_iter = std::next(pool_.rbegin());
                 element_iter != pool_.rend(); prev_element_iter = element_iter++) {
                element_iter->next_free = &*prev_element_iter;
            }
            first_free_ = &*prev_element_iter;
        };

        pool(const pool &other) = delete;

        pool &operator=(const pool &other) = delete;

        pool(pool &&other) noexcept = default;

        pool &operator=(pool &&other) noexcept = default;

        template<class Tp, class... Args>
        auto emplace(Args &&... args) -> Tp & {
            ++size_;
            assert(first_free_);
            element_type *storage = first_free_;
            first_free_ = first_free_->next_free;
            new(storage) Tp(std::forward<Args>(args)...);
            return storage->value;
        }

        auto insert(const T &val) -> T & {
            return emplace(val);
        }

        auto insert(T &&val) -> T & {
            return emplace(std::move(val));
        }

        void remove(T *val) {
            --size_;
            auto *element = static_cast<element_type *>(val);
            assert(element >= pool_.data());
            assert(element - pool_.data() < pool_.size());
            if constexpr (!std::is_trivially_destructible_v<T>) {
                element->value.~T();
            }
            element->next_free = first_free_;
            first_free_ = element;
        }

        [[nodiscard]] auto empty() const -> bool {
            return !first_free_;
        }

        [[nodiscard]] auto size() const -> size_type {
            return size_;
        }

        [[nodiscard]] auto capacity() const -> size_type {
            return pool_.size();
        }
    };

    template<class T>
    class iterable_pool {
    protected:
        template<bool>
        class pool_iterator;
    public:
        using size_type = std::size_t;

        using const_iterator = pool_iterator<true>;
        using iterator = pool_iterator<false>;

    protected:
        T* pool_;
        dynamic_bitset<> free_blocks_;
        size_type size_, capacity_;
    public:
        explicit iterable_pool(size_type size) : pool_(static_cast<T*>(malloc(size * sizeof(T)))), free_blocks_(size), size_(0), capacity_(size) {
            free_blocks_.set();
            assert(free_blocks_.all());
        };

        iterable_pool(const iterable_pool &other) = delete;

        iterable_pool &operator=(const iterable_pool &other) = delete;

        iterable_pool(iterable_pool &&other) noexcept = default;

        iterable_pool &operator=(iterable_pool &&other) noexcept = default;

        template<class Tp, class... Args>
        auto emplace(Args &&... args) -> Tp & {
            ++size_;
            auto next_free = _find_next_free();
            T *storage = pool_ + _find_next_free();
            new(storage) Tp(std::forward<Args>(args)...);
            free_blocks_.reset(next_free);
            return *storage;
        }

        auto insert(const T &val) -> T & {
            return emplace<T>(val);
        }

        auto insert(T &&val) -> T & {
            return emplace<T>(std::move(val));
        }

        void remove(T *val) {
            --size_;
            assert(val >= pool_);
            assert(val - pool_ < capacity());
            if constexpr (!std::is_trivially_destructible_v<T>) {
                val->~T();
            }
            free_blocks_.set(val - pool_);
        }

        [[nodiscard]] auto begin() -> iterator {
            return iterator(*this);
        }

        [[nodiscard]] auto begin() const -> const_iterator {
            return const_iterator(*this);
        }

        [[nodiscard]] auto end() -> iterator {
            return iterator(*this, capacity());
        }

        [[nodiscard]] auto end() const -> const_iterator {
            return const_iterator(*this, capacity());
        }

        [[nodiscard]] auto empty() const -> bool {
            return size_ == 0;
        }

        [[nodiscard]] auto size() const -> size_type {
            return size_;
        }

        [[nodiscard]] auto capacity() const -> size_type {
            return capacity_;
        }

    protected:
        [[nodiscard]] auto _find_next_free() const -> size_type {
            assert(size() < capacity());
            return free_blocks_.find_first();
        }

        [[nodiscard]] auto _get(size_type index) -> T& {
            return pool_[index];
        }

        [[nodiscard]] auto _get(size_type index) const -> const T& {
            return pool_[index];
        }

    protected:
        template<bool is_const>
        class pool_iterator {
        public:
                using value_type = std::conditional_t<is_const, const T, T>;
                using reference_type = value_type&;
                using difference_type = std::ptrdiff_t;
                using iterator_category = std::forward_iterator_tag;
        protected:
                using pool_type = std::conditional_t<is_const, const iterable_pool, iterable_pool>;

                pool_type &pool_;
                size_type index_;

                void _inc() {
                    for(index_ += 1;index_ < pool_.capacity() && pool_.free_blocks_.test(index_); ++index_) {}
                }
        public:
                explicit pool_iterator(pool_type &pool) : pool_(pool), index_(0) {
                    if(pool_.free_blocks_.test(index_) && pool_.capacity() > 0) _inc();
                }

                pool_iterator(pool_type &pool, size_type index) : pool_(pool), index_(index) {}

                value_type       operator*()             {return pool_._get(index_);}
                const value_type operator*()       const {return pool_._get(index_);}

                pool_iterator& operator++()       {_inc();return *this;}
                pool_iterator  operator++(int)    {pool r(*this);_inc();return r;}

                bool operator!=(const pool_iterator &r) const {return index_ != r.index_;}
                bool operator==(const pool_iterator &r) const {return index_ == r.index_;}
        };
    };

}

#endif //ROUGELIKE_DEV_POOL_HPP
