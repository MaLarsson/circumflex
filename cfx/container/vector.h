#pragma once

#ifndef CFX_CONTAINER_VECTOR_H_
#define CFX_CONTAINER_VECTOR_H_

#include "cfx/allocator/mallocator.h"

namespace cfx {

template <typename T, typename A = cfx::mallocator>
class vector {
 public:
    using value_type = T;
    using allocator_type = A;

    // Constructors
    vector() noexcept(noexcept(allocator_type()))
	: vector(allocator_type()) {}

    explicit vector(const allocator_type& alloc) noexcept
	: alloc_(alloc) {}

 private:
    T* head_;
    block blk_;
    allocator_type alloc_;

    T* start() { return static_cast<T*>(blk_.start); }
    T* end() { return static_cast<T*>(blk_.end); }
};

} // cfx

#endif // CFX_CONTAINER_VECTOR_H_
