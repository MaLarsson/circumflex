#pragma once

#ifndef CFX_ALLOCATOR_STACK_ALLOCATOR_H_
#define CFX_ALLOCATOR_STACK_ALLOCATOR_H_

#include <cstddef>

#include "cfx/allocator/block.h"

namespace cfx {

template <size_t N>
class stack_allocator {
 public:
    cfx::block allocate(size_t size) noexcept {
	// TODO ...

	return { nullptr, nullptr };
    }

    void deallocate(cfx::block& blk) noexcept {
	// TODO ...
    }

    bool owns(const cfx::block& blk) const noexcept {
	return blk && blk.start >= stack_ && blk.start < stack_ + N;
    }

 private:
    std::byte stack_[N];
    std::byte* head_;
};

} // cfx

#endif // CFX_ALLOCATOR_STACK_ALLOCATOR_H_
