#pragma once

#ifndef CFX_ALLOCATOR_BLOCK_H_
#define CFX_ALLOCATOR_BLOCK_H_

#include <cstddef>

namespace cfx {

struct block {
    // Constructors
    block() noexcept : start(nullptr), end(nullptr) {}

    block(std::byte* start, std::byte* end) noexcept
	: start(start), end(end) {}

    block(const block& blk) noexcept = default;
    block(block&& blk) noexcept = default;

    // Operators
    explicit operator bool() const { return start != nullptr && end != nullptr; }

    // Methods
    size_t size() const noexcept { return end - start; }

    void reset() noexcept {
	start = nullptr;
	end = nullptr;
    }

    // Fields
    std::byte* start;
    std::byte* end;
};

} // cfx

#endif // CFX_ALLOCATOR_BLOCK_H_
