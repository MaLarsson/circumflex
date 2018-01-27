#ifndef CFX_CONTAINER_INLINED_VECTOR_H_
#define CFX_CONTAINER_INLINED_VECTOR_H_

#include <cstddef>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

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

    inlined_vector(std::initializer_list<value_type> list,
		   const allocator_type& alloc = allocator_type())
	: alloc_(alloc), blk_(alloc_.allocate(std::max(list.size(), N))), head_(start()) {
	for (auto& elem : list)
	    construct(head_++, elem);
    }

    // Element access
    reference at(size_type pos) {
	if (!(pos < size()))
	    throw std::out_of_range("cfx::inlined_vector::at() failed bounds check");

	return start()[pos];
    }

    const_reference at(size_type pos) const {
	if (!(pos < size()))
	    throw std::out_of_range("cfx::inlined_vector::at() failed bounds check");

	return start()[pos];
    }

    reference operator[](size_type pos) { return start()[pos]; }
    const_reference operator[](size_type pos) const { return start()[pos]; }

    reference front() { return at(0); }
    const_reference front() const { return at(0); }

    reference back() { return at(size() - 1); }
    const_reference back() const { return at(size() - 1); }

    pointer data() noexcept { return start(); }
    const_pointer data() const noexcept { return start(); }

    // Iterators
    iterator begin() noexcept { return start(); }
    const_iterator begin() const noexcept { return start(); }
    const_iterator cbegin() const noexcept { return begin(); }

    iterator end() noexcept { return head_; }
    const_iterator end() const noexcept { return head_; }
    const_iterator cend() const noexcept { return end(); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return  const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return  const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return rend(); }

    // Capacity
    bool empty() const noexcept { return size() == 0; }
    size_type size() const noexcept { return head_ - start(); }
    size_type capacity() const noexcept { return end_cap() - start(); }

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

    pointer start() const noexcept { return static_cast<pointer>(blk_.start); }
    pointer end_cap() const noexcept { return static_cast<pointer>(blk_.end); }

    template <typename ...Args>
    reference construct(pointer ptr, Args&&... args) {
	::new (static_cast<void*>(ptr)) value_type(std::forward<Args>(args)...);
	return *ptr;
    }
};

} // cfx

#endif // CFX_CONTAINER_INLINED_VECTOR_H_
