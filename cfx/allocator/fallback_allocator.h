#pragma once

#ifndef CFX_ALLOCATOR_FALLBACK_ALLOCATOR_H_
#define CFX_ALLOCATOR_FALLBACK_ALLOCATOR_H_

#include <cstddef>

#include "cfx/allocator/block.h"
#include "cfx/allocator/traits.h"

namespace cfx {

template <typename P, typename F>
class fallback_allocator {
    using primary = P;
    using fallback = F;

    static_assert(cfx::implements_owns_v<P>, "primary allocator does not implement owns");

 public:
    cfx::block allocate(size_t size) noexcept {
	if (auto blk = primary::allocate(size))
	    return blk;

	return fallback::allocate(size);
    }

    bool reallocate(cfx::block& blk, size_t new_size) noexcept {
	// TODO ...

	return false;
    }

    void deallocate(cfx::block& blk) noexcept {
	if (primary::owns(blk))
	    primary::deallocate(blk);
	else
	    fallback::deallocate(blk);
    }

    typename std::enable_if_t<cfx::implements_owns_v<P> && cfx::implements_owns_v<F>, bool>
    owns(const cfx::block& blk) const noexcept {
	return primary::owns(blk) || fallback::owns(blk);
    }
};

} // cfx

#endif // CFX_ALLOCATOR_FALLBACK_ALLOCATOR_H_
