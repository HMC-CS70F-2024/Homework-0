/*
 * show-rep-internals.hpp
 *
 * YOU DON"T HAVE TO LOOK AT THIS FILE!
 *
 * This code uses some advanced C++ features we haven't learned about yet,
 * so may look a bit strange.  You can look at it if you like, but it's not
 * worth spending a lot of time trying to understand.
 */

#ifndef SHOW_REP_INTERNALS_HPP_INCLUDED
#define SHOW_REP_INTERNALS_HPP_INCLUDED

#include <cstring>
#include <climits>
#include <iostream>
#include <bitset>
#include <string>
#include <limits>
#include <type_traits>
#include <cctype>

// From https://stackoverflow.com/a/64490578/847987, “Is it possible to print
// a variable's type in standard C++?”

#include <string_view>
template <typename T>
constexpr std::string_view type_name();

template <>
constexpr std::string_view type_name<void>() {
    return "void";
}

namespace detail {

using type_name_prober = void;

template <typename T>
constexpr std::string_view wrapped_type_name() {
#ifdef __clang__
    return __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
    return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
    return __FUNCSIG__;
#else
#error "Unsupported compiler"
#endif
}

constexpr std::size_t wrapped_type_name_prefix_length() {
    return wrapped_type_name<type_name_prober>().find(
        type_name<type_name_prober>());
}

constexpr std::size_t wrapped_type_name_suffix_length() {
    return wrapped_type_name<type_name_prober>().length()
           - wrapped_type_name_prefix_length()
           - type_name<type_name_prober>().length();
}

}  // namespace detail

template <typename T>
constexpr std::string_view type_name() {
    constexpr auto wrapped_name = detail::wrapped_type_name<T>();
    constexpr auto prefix_length = detail::wrapped_type_name_prefix_length();
    constexpr auto suffix_length = detail::wrapped_type_name_suffix_length();
    constexpr auto type_name_length =
        wrapped_name.length() - prefix_length - suffix_length;
    return wrapped_name.substr(prefix_length, type_name_length);
}


template <typename T>
constexpr bool is_char_v = std::is_same_v<std::remove_cv_t<T>, char> ||
                           std::is_same_v<std::remove_cv_t<T>, signed char> ||
                           std::is_same_v<std::remove_cv_t<T>, unsigned char>;


template <typename T>
void show_representation(const T& value) {
    // If T is a floating point type, set the precision to the maximum
    // number of digits we can represent.
    int saved_precision;
    if constexpr (std::is_floating_point_v<T>) {
        saved_precision = std::cout.precision();
        std::cout.precision(std::numeric_limits<T>::max_digits10);
    }
    std::cout << type_name<T>() << "{";
    // If it's an array, print out the elements separated by commas.
    if constexpr (std::is_array_v<T>) {
        constexpr size_t NUM_ELEMENTS = sizeof(value) / sizeof(*value);
        for (size_t i = 0; i < NUM_ELEMENTS; ++i) {
            if (i != 0) {
                std::cout << ", ";
            }
            // If value[i] is a character, put quotes around it.
            if constexpr (is_char_v<std::remove_reference_t<decltype(value[i])>>) {
                std::cout << "'" << value[i] << "'";
            } else {
                std::cout << value[i];
            }
        }
    } else {
        // If it's a character (of any kind, including signed or unsigned)
        if constexpr (is_char_v<T>) {
            // ... but only if it's printable.
            if (std::isprint(value)) {
                std::cout << "'" << value << "'";
            } else {
                std::cout << static_cast<int>(value);
            }
        } else {
            std::cout << value;
        }
    }
    std::cout << "}"
              << " occupies " << sizeof(T) << " byte"
              << (sizeof(T) == 1 ? "" : "s") << ", bits are:";
    if constexpr (std::is_floating_point_v<T>) {
        std::cout.precision(saved_precision);
    }
    static T copy;  // For technical reasons, we duplicate the value
                    // in a static variable.  This ensures that any
                    // unused bits will be zero.
    // We also need to detect whether or not the type is a primitive
    // array, if so we need to copy elements one at a time.
    if constexpr (std::is_array_v<T>) {
        constexpr size_t NUM_ELEMENTS = sizeof(value) / sizeof(*value);
        for (size_t i = 0; i < NUM_ELEMENTS; ++i) {
            copy[i] = value[i];
        }
    } else {
        copy = value;
    }
    unsigned char memory_copy[sizeof(T)];
    memcpy(&memory_copy[0], &copy, sizeof(T));
    for (size_t i = 0; i < sizeof(T); ++i) {
        if (i % 8 == 0) {
            std::cout << "\n  ";
        } else {
            std::cout << " ";
        }
        std::cout << std::bitset<CHAR_BIT>(memory_copy[i]);
    }
    std::cout << "\n";
}

#endif  // SHOW_REP_INTERNALS_HPP_INCLUDED
