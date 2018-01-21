#pragma once

#ifndef CFX_ALLOCATOR_TRAITS_H_
#define CFX_ALLOCATOR_TRAITS_H_

namespace cfx {

template <typename T>
struct implements_owns {
    template <typename U, bool (U::*)() const noexcept> struct check {};
    template <typename U> static constexpr bool test(check<U, &U::owns>*) { return true; }
    template <typename U> static constexpr bool test(...) { return false; }

    static constexpr bool value = test<T>(nullptr);
};

template <typename T>
constexpr bool implements_owns_v = implements_owns<T>::value;

} // cfx

#endif // CFX_ALLOCATOR_TRAITS_H_
