#ifndef CFX_ALLOCATOR_FALLBACK_ALLOCATOR_H_
#define CFX_ALLOCATOR_FALLBACK_ALLOCATOR_H_

#include <cstddef>
#include <type_traits>

#include "cfx/allocator/block.h"
#include "cfx/allocator/traits.h"

namespace cfx {

template <typename Primary, typename Fallback>
class fallback_allocator : private Primary, private Fallback {
    static_assert(cfx::implements_owns_v<Primary>, "primary allocator does not implement owns");

 public:
    cfx::block allocate(size_t size) noexcept {
	if (auto blk = Primary::allocate(size))
	    return blk;

	return Fallback::allocate(size);
    }

    void deallocate(cfx::block& blk) noexcept {
	if (Primary::owns(blk))
	    Primary::deallocate(blk);
	else
	    Fallback::deallocate(blk);
    }

    template <typename U = Primary, typename V = Fallback>
    typename std::enable_if_t<cfx::implements_owns_v<U> && cfx::implements_owns_v<V>, bool>
    owns(const cfx::block& blk) const noexcept {
	return Primary::owns(blk) || Fallback::owns(blk);
    }
};

} // cfx

#endif // CFX_ALLOCATOR_FALLBACK_ALLOCATOR_H_
