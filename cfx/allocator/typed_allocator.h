#ifndef CFX_ALLOCATOR_TYPED_ALLOCATOR_H_
#define CFX_ALLOCATOR_TYPED_ALLOCATOR_H_

#include <cstddef>
#include <type_traits>

#include "cfx/allocator/block.h"
#include "cfx/allocator/traits.h"

namespace cfx {

template <typename T, typename Alloc>
class typed_allocator : private Alloc {
 public:
    cfx::block allocate(size_t n) noexcept {
	return Alloc::allocate(sizeof(T) * n);
    }

    void deallocate(cfx::block& blk) noexcept {
	return Alloc::deallocate(blk);
    }

    template <typename U = Alloc>
    typename std::enable_if_t<cfx::implements_owns_v<U>, bool>
    owns(const cfx::block& blk) const noexcept {
	return Alloc::owns(blk);
    }
};

}

#endif // CFX_ALLOCATOR_TYPED_ALLOCATOR_H_
