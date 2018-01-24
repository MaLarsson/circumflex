#pragma once

#ifndef CFX_ALLOCATOR_FALLBACK_ALLOCATOR_H_
#define CFX_ALLOCATOR_FALLBACK_ALLOCATOR_H_

#include <cstddef>
#include <type_traits>

#include "cfx/allocator/block.h"
#include "cfx/allocator/traits.h"

namespace cfx {

template <typename P, typename F>
class fallback_allocator : private P, private F {
    using primary = P;
    using fallback = F;

    static_assert(cfx::implements_owns_v<primary>, "primary allocator does not implement owns");

 public:
    cfx::block allocate(size_t size) noexcept {
	if (auto blk = primary::allocate(size))
	    return blk;

	return fallback::allocate(size);
    }

    void deallocate(cfx::block& blk) noexcept {
	if (primary::owns(blk))
	    primary::deallocate(blk);
	else
	    fallback::deallocate(blk);
    }

    template <typename U = primary, typename V = fallback>
    typename std::enable_if_t<cfx::implements_owns_v<U> && cfx::implements_owns_v<V>, bool>
    owns(const cfx::block& blk) const noexcept {
	return primary::owns(blk) || fallback::owns(blk);
    }
};

} // cfx

#endif // CFX_ALLOCATOR_FALLBACK_ALLOCATOR_H_
