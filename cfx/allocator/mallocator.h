#pragma once

#ifndef CFX_ALLOCATOR_MALLOCATOR_H_
#define CFX_ALLOCATOR_MALLOCATOR_H_

#include "block.h"

namespace cfx {

class mallocator {
 public:
    block allocate(size_t size) noexcept {
	if (auto start = ::malloc(size); start != nullptr)
	    return { start, static_cast<char*>(start) + size };

	return { nullptr, nullptr };
    }

    void deallocate(block& blk) noexcept {
	::free(blk.start);
	blk.reset();
    }
};

} // cfx

#endif // CFX_ALLOCATOR_MALLOCATOR_H_
