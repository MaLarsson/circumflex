#ifndef CFX_ALLOCATOR_BLOCK_H_
#define CFX_ALLOCATOR_BLOCK_H_

namespace cfx {

struct block {
    // Constructors
    block() noexcept : start(nullptr), end(nullptr) {}

    block(void* start, void* end) noexcept
	: start(start), end(end) {}

    // Operators
    explicit operator bool() const { return start != nullptr && end != nullptr; }

    void reset() noexcept {
	start = nullptr;
	end = nullptr;
    }

    // Fields
    void* start;
    void* end;
};

} // cfx

#endif // CFX_ALLOCATOR_BLOCK_H_
