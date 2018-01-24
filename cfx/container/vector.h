#pragma once

#ifndef CFX_CONTAINER_VECTOR_H_
#define CFX_CONTAINER_VECTOR_H_

#include <cstddef>
#include <iterator>
#include <utility>

#include "cfx/allocator/block.h"
#include "cfx/allocator/fallback_allocator.h"
#include "cfx/allocator/stack_allocator.h"
#include "cfx/allocator/mallocator.h"

namespace cfx {

template <size_t N>
using locallocator = cfx::fallback_allocator<cfx::stack_allocator<N>, cfx::mallocator>;

template <typename T, size_t N = 10, typename A = locallocator<sizeof(T) * N> >
class vector {
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
    vector() noexcept(noexcept(allocator_type()))
	: vector(allocator_type()) {}

    explicit vector(const allocator_type& alloc) noexcept
	: blk_(cfx::block()), head_(nullptr), alloc_(alloc) {}

    // Modifiers
    template <typename ...Args>
    reference emplace_back(Args&&... args) {
	return construct(head_++, std::forward<Args>(args)...);
    }

    void push_back(const_reference value) { emplace_back(value); }
    void push_back(value_type&& value) { emplace_back(std::move(value)); }

 private:
    cfx::block blk_;
    pointer head_;
    allocator_type alloc_;

    pointer start() { return static_cast<pointer>(blk_.start); }
    pointer end() { return static_cast<pointer>(blk_.end); }

    template <typename ...Args>
    reference construct(pointer ptr, Args&&... args) {
	::new (static_cast<void*>(ptr)) value_type(std::forward<Args>(args)...);
	return *ptr;
    }
};

} // cfx

#endif // CFX_CONTAINER_VECTOR_H_
