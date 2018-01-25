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
	// TODO ...

	return { nullptr, nullptr };
    }

    void deallocate(cfx::block& blk) noexcept {
	// TODO ...
    }

    bool owns(const cfx::block& blk) const noexcept {
	return blk && blk.start >= stack_ && blk.start < stack_ + Size;
    }

 private:
    static_assert(Size > 0, "stack allocator with non positive size");
    static_assert(Alignment > 0, "stack allocator with non positive alignment");

    alignas(Alignment) std::byte stack_[Size];
    std::byte* head_;
};

} // cfx

#endif // CFX_ALLOCATOR_STACK_ALLOCATOR_H_
