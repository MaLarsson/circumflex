#ifndef CFX_CONTAINER_INLINED_VECTOR_H_
#define CFX_CONTAINER_INLINED_VECTOR_H_

#include <cstddef>
#include <iterator>
#include <utility>

#include "cfx/allocator/block.h"
#include "cfx/allocator/typed_allocator.h"
#include "cfx/allocator/fallback_allocator.h"
#include "cfx/allocator/stack_allocator.h"
#include "cfx/allocator/mallocator.h"

namespace cfx {

template <typename T, size_t N>
using locallocator = cfx::typed_allocator<T,
    cfx::fallback_allocator<
	cfx::stack_allocator<sizeof(T) * N, alignof(T)>,
	cfx::mallocator
    >
>;

template <typename T, size_t N = 10, typename A = locallocator<T, N> >
class inlined_vector {
 public:
    // Aliases
    using value_type = T;
    using allocator_type = A;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Constructors
    explicit inlined_vector(const allocator_type& alloc = allocator_type()) noexcept
	: alloc_(alloc), blk_(alloc_.allocate(N)), head_(start()) {}

    // Iterators
    iterator begin() noexcept { return start(); }
    iterator end() noexcept { return head_; }

    // Modifiers
    template <typename ...Args>
    reference emplace_back(Args&&... args) {
	return construct(head_++, std::forward<Args>(args)...);
    }

    void push_back(const_reference value) { emplace_back(value); }
    void push_back(value_type&& value) { emplace_back(std::move(value)); }

 private:
    static_assert(N > 0, "inlined vector with non positive size");

    allocator_type alloc_;
    cfx::block blk_;
    pointer head_;

    pointer start() { return static_cast<pointer>(blk_.start); }
    pointer end_cap() { return static_cast<pointer>(blk_.end); }

    template <typename ...Args>
    reference construct(pointer ptr, Args&&... args) {
	::new (static_cast<void*>(ptr)) value_type(std::forward<Args>(args)...);
	return *ptr;
    }
};

} // cfx

#endif // CFX_CONTAINER_INLINED_VECTOR_H_
