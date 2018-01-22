#pragma once

#ifndef CFX_ALLOCATOR_TRAITS_H_
#define CFX_ALLOCATOR_TRAITS_H_

#include "cfx/allocator/block.h"

namespace cfx {

template <typename T>
struct implements_owns {
    template <typename U, bool (U::*)(const cfx::block&) const noexcept> struct fn_sig {};
    template <typename U> static constexpr bool check(fn_sig<U, &U::owns>*) { return true; }
    template <typename U> static constexpr bool check(void*) { return false; }

    static constexpr bool value = check<T>(nullptr);
};

template <typename T>
constexpr bool implements_owns_v = implements_owns<T>::value;

} // cfx

#endif // CFX_ALLOCATOR_TRAITS_H_
