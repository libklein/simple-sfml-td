//
// Created by patrick on 10/01/2020.
//

#ifndef DYN_BITSET_H
#define DYN_BITSET_H

#include <type_traits>
#include <limits>
#include <array>

namespace util {

    /*
     * https://stackoverflow.com/questions/17375743/what-library-do-i-have-to-use-for-ctz-command-in-c
     */

    template<std::size_t num_bits, typename Block>
    class static_bitset {
        static_assert(std::is_integral_v<Block> && std::is_unsigned_v<Block> && num_bits > 0);

        constexpr static auto _NUM_BLOCKS() -> std::size_t {
            return ((num_bits - 1) / BITS_PER_BLOCK) + 1;
        }
    protected:
        constexpr static auto BITS_PER_BLOCK = std::numeric_limits<Block>::digits;
        constexpr static auto NUM_BLOCKS = _NUM_BLOCKS();

        /**
         * blocks_[0] is the block containing the LSB, blocks_[NUM_BLOCKS-1] contains the MSB.
         */
        std::array<Block, NUM_BLOCKS> blocks_{}; // Default initialize to 0

        [[nodiscard]] constexpr auto get_block(size_t n) -> Block& {
            return blocks_[n];
        }

        [[nodiscard]] constexpr auto get_block(size_t n) const -> Block {
            return blocks_[n];
        }

        constexpr void set_block(size_t n, Block val) {
            blocks_[n] = val;
        }

        /**
         * Get block and offset in block from index.
         * @param index
         * @return A pair of [block_id, offset]
         */
        [[nodiscard]] constexpr auto get_pos(size_t index) const -> std::pair<size_t, size_t> {
            size_t block_id = index / BITS_PER_BLOCK;
            return {block_id, index - (block_id * BITS_PER_BLOCK)};
        }

    public:
        using size_t = std::size_t;
        constexpr static auto n_pos = std::numeric_limits<size_t>::max();
    private:
        size_t size_ = 0;
    public:

        static_bitset() = default;

        explicit static_bitset(size_t size) : size_(size) {
            if(size > num_bits) throw std::runtime_error("Cannot resize to larger size than statically allocated");
        };

        [[nodiscard]] constexpr auto size() const -> size_t {
            return size_;
        }

        void resize(size_t size) {
            if(size > num_bits) throw std::runtime_error("Cannot resize to larger size than statically allocated");
            size_ = size;
        }

        constexpr void clear() {
            std::fill(blocks_.begin(), blocks_.end(), 0);
        }

        constexpr auto operator&=(static_bitset const& other) -> static_bitset& {
            for(unsigned int i = 0; i < NUM_BLOCKS; ++i) {
                get_block(i) &= other.get_block(i);
            }
            return *this;
        }

        constexpr auto operator|=(static_bitset const& other) -> static_bitset& {
            for(unsigned int i = 0; i < NUM_BLOCKS; ++i) {
                get_block(i) |= other.get_block(i);
            }
            return *this;
        }

        constexpr auto operator^=(static_bitset const& other) -> static_bitset& {
            for(unsigned int i = 0; i < NUM_BLOCKS; ++i) {
                get_block(i) ^= other.get_block(i);
            }
            return *this;
        }

        constexpr auto operator<<=(size_t n) -> static_bitset& {
            size_t block_offset = n / BITS_PER_BLOCK;
            size_t intra_block_offset = n - block_offset*BITS_PER_BLOCK;
            // Copy
            for(unsigned int i = NUM_BLOCKS; i-- > block_offset + 1;) {
                get_block(i) = (get_block(i-block_offset) << intra_block_offset)
                        | (get_block(i - block_offset - 1) >> (BITS_PER_BLOCK - i));
            }
            // Handle special case middle block
            get_block(block_offset) = get_block(0) << intra_block_offset;
            // Clear blocks < offset
            for(unsigned int i = 0; i < block_offset;++i) {
                set_block(i, static_cast<Block>(0));
            }
            return *this;
        }

        constexpr auto operator>>=(size_t n) -> static_bitset& {
            size_t block_offset = n / BITS_PER_BLOCK;
            size_t intra_block_offset = n - block_offset*BITS_PER_BLOCK;
            for(unsigned int i = 0; i < block_offset - 1; ++i) {
                get_block(i) = (get_block(i+block_offset) >> intra_block_offset)
                        | (get_block(i+block_offset+1) << (BITS_PER_BLOCK - i));
            }
            get_block(block_offset) = get_block(NUM_BLOCKS-1) >> intra_block_offset;
            for(unsigned int i = block_offset + 1; i < NUM_BLOCKS; ++i) {
                set_block(i, 0);
            }
            return *this;
        }

        [[nodiscard]] constexpr auto operator<<(size_t n) const -> static_bitset {
            auto b = *this;
            b <<= n;
            return b;
        }

        [[nodiscard]] constexpr auto operator>>(size_t n) const -> static_bitset {
            auto b = *this;
            b >>= n;
            return b;
        }

        constexpr auto operator~() const -> static_bitset {
            static_bitset b;
            for(unsigned int i = 0; i < NUM_BLOCKS; ++i) {
                b.get_block(i) = ~get_block(i);
            }
            return *this;
        }

        constexpr void set() {
            std::fill(blocks_.begin(), blocks_.end(), std::numeric_limits<Block>::max());
        }

        constexpr void set(size_t n) {
            auto [block, offset] = get_pos(n);
            blocks_[block] |= static_cast<Block>(1) << offset;
        }

        /**
         * Sets all bits in the range [n, end)
         * @param n
         * @return
         */
        constexpr void set_above(size_t n) {
            auto [block, offset] = get_pos(n);
            blocks_[block] |= ~((static_cast<Block>(1) << (offset+1)) - static_cast<Block>(1));
            for(unsigned int i = block + 1; i < NUM_BLOCKS; ++i) {
                set_block(i, std::numeric_limits<Block>::max());
            }
        }

        /**
         * Sets all bits in the range [begin, n)
         * @param n
         * @return
         */
        constexpr void set_below(size_t n) {
            auto [block, offset] = get_pos(n);
            for(unsigned int i = 0; i < block; ++i) {
                set_block(i, std::numeric_limits<Block>::max());
            }
            blocks_[block] |= (static_cast<Block>(1) << offset) - static_cast<Block>(1);
        }

        constexpr void reset() {
            clear();
        }

        constexpr void reset(size_t n) {
            auto [block, offset] = get_pos(n);
            get_block(block) &= ~(static_cast<Block>(1) << offset);
        }

        /**
         * Resets all bits in the range [n, end)
         * @param n
         * @return
         */
        constexpr void reset_above(size_t n) {
            auto [block, offset] = get_pos(n);
            blocks_[block] &= (static_cast<Block>(1) << offset) - static_cast<Block>(1);
            for(unsigned int i = block + 1; i < NUM_BLOCKS; ++i) {
                set_block(i, static_cast<Block>(0));
            }
        }

        /**
         * Resets all bits in the range [begin, n)
         * @param n
         * @return
         */
        constexpr void reset_below(size_t n) {
            auto [block, offset] = get_pos(n);
            for(unsigned int i = 0; i < block; ++i) {
                set_block(i, static_cast<Block>(0));
            }
            blocks_[block] &= ~((static_cast<Block>(1) << offset) - static_cast<Block>(1));
        }

        constexpr void flip() {
            for(unsigned int i = 0; i < NUM_BLOCKS; ++i) blocks_[i] = ~blocks_[i];
        }

        constexpr void flip(size_t n) {
            auto [block, offset] = get_pos(n);
            get_block(block) ^= static_cast<Block>(1) << offset;
        }

        [[nodiscard]] constexpr auto test(size_t n) const -> bool {
            auto [block, offset] = get_pos(n);
            return (get_block(block) >> offset) & 1;
        }

        [[nodiscard]] constexpr auto all() const -> bool {
            for(Block block : blocks_) {
                if(block != std::numeric_limits<Block>::max()) return false;
            }
            return true;
        }

        [[nodiscard]] constexpr auto any() const -> bool {
            for(Block block : blocks_) {
                if(block != static_cast<Block>(0)) return true;
            }
            return false;
        }

        [[nodiscard]] constexpr auto none() const -> bool {
            for(Block block : blocks_) {
                if(block != static_cast<Block>(0)) return false;
            }
            return true;
        }

        [[nodiscard]] constexpr auto count() const -> size_t {
            size_t c = 0;
            for(unsigned int i = 0; i < NUM_BLOCKS; ++i) {
                c += __builtin_popcountll(get_block(i));
            }
            return c;
        }

        [[nodiscard]] constexpr auto find_first() const -> size_t {
            // Possible optimization: keep track of first block with 1 bit set
            for(unsigned int i = 0; i < NUM_BLOCKS; ++i) {
                if(get_block(i) == static_cast<Block>(0)) continue;
                return __builtin_ctzll(get_block(i)) + i * BITS_PER_BLOCK;
            }
            return n_pos;
        }

        [[nodiscard]] constexpr auto find_last() const -> size_t {
            // Possible optimization: keep track of last block with 1 bit set
            for(unsigned int i = NUM_BLOCKS; i-->=1;){
                if(get_block(i) == static_cast<Block>(0)) continue;
                return (BITS_PER_BLOCK - __builtin_clzll(get_block(i)) - 1) + BITS_PER_BLOCK*i;
            }
            return n_pos;
        }

        /**
         * Finds the first position > offset which is 1 or npos if no bit > offset is set
         * @param offset
         * @return
         */
        [[nodiscard]] constexpr auto find_next(size_t offset) const -> size_t {
            auto [block, offset_in_block] = get_pos(offset);
            Block b = get_block(block) >> (offset_in_block + 1);
            if(offset_in_block != BITS_PER_BLOCK - 1) {
                if (b != static_cast<Block>(0)) return __builtin_ctzll(b) + offset + 1;
            }

            for(unsigned int i = block+1; i < NUM_BLOCKS;++i) {
                b = get_block(i);
                if(b == static_cast<Block>(0)) continue;
                return __builtin_ctzll(b) + i*BITS_PER_BLOCK;
            }
            return n_pos;
        }

        constexpr auto operator==(static_bitset const& other) const -> bool {
            bool is_eq = true;
            for(unsigned int block_id = 0; block_id < NUM_BLOCKS; ++block_id) {
                is_eq &= this->get_block(block_id) == other.get_block(block_id);
            }
            return is_eq;
        }

        friend auto operator<<(std::ostream& out, static_bitset const& bitset) -> std::ostream& {
            for(size_t i = 0; i < bitset.size(); ++i) {
                out << (bitset.test(i) ? '1' : '0');
            }
            return out;
        }
    };
}  // namespace Utility

#endif //WAREHOUSING_BITSET_H
