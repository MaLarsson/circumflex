#pragma once

#ifndef CFX_ALLOCATOR_MALLOCATOR_H_
#define CFX_ALLOCATOR_MALLOCATOR_H_

#include <cstddef>
#include <cstdlib>

#include "cfx/allocator/block.h"

namespace cfx {

class mallocator {
 public:
    cfx::block allocate(size_t size) noexcept {
	if (auto start = static_cast<std::byte*>(::malloc(size)); start != nullptr)
	    return { start, start + size };

	return { nullptr, nullptr };
    }

    bool reallocate(cfx::block& blk, size_t new_size) noexcept {
	if (auto new_start = ::realloc(blk.start, new_size); new_start != nullptr) {
	    blk.start = static_cast<std::byte*>(new_start);
	    blk.end = blk.start + new_size;

	    return true;
	}

	return false;
    }

    void deallocate(cfx::block& blk) noexcept {
	::free(blk.start);
	blk.reset();
    }
};

} // cfx

#endif // CFX_ALLOCATOR_MALLOCATOR_H_
