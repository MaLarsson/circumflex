#ifndef CFX_ALLOCATOR_STACK_ALLOCATOR_H_
#define CFX_ALLOCATOR_STACK_ALLOCATOR_H_

#include <cstddef>
#include <type_traits>

#include "cfx/allocator/block.h"

namespace cfx {

template <size_t Size, size_t Alignment>
class stack_allocator {
 public:
    stack_allocator() noexcept : head_(stack_) {}

    cfx::block allocate(size_t size) noexcept {
	auto aligned_size = round_to_alignment(size);

	if (aligned_size > remaining_size())
	    return { nullptr, nullptr };

	auto start = head_;
	head_ = head_ + aligned_size;

	return { start, head_ };
    }

    void deallocate(cfx::block& /*blk*/) noexcept {
	// TODO ...
    }

    bool owns(const cfx::block& blk) const noexcept {
	return blk && blk.start >= stack_ && blk.start < stack_ + Size;
    }

 private:
    static_assert(Size > 0, "stack allocator with non positive size");
    static_assert(Alignment > 0, "stack allocator with non positive alignment");

    std::byte stack_[Size];
    std::byte* head_;

    size_t remaining_size() const noexcept { return stack_ + Size - head_; }

    constexpr size_t round_to_alignment(size_t size) noexcept {
        return size + ((size % Alignment == 0) ? 0 : (Alignment - size % Alignment));
    }
};

} // cfx

#endif // CFX_ALLOCATOR_STACK_ALLOCATOR_H_
