/*
 * show-types-internals.hpp
 *
 * YOU DON"T HAVE TO LOOK AT THIS FILE!
 *
 * This code uses some advanced C++ features we haven't learned about yet,
 * so may look a bit strange.  You can look at it if you like, but it's not
 * worth spending a lot of time trying to understand.
 *
 * If you do want to know more about how it's doing what it's doing, it's
 * probably better to read this web page:
 *
 *      https://en.cppreference.com/w/cpp/types/numeric_limits
 */

#ifndef SHOW_TYPES_INTERNALS_HPP_INCLUDED
#define SHOW_TYPES_INTERNALS_HPP_INCLUDED
#include <limits>
#include <string>
#include <type_traits>

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

/*
 * To avoid lots of copy-and-pasted code, this function uses an advanced
 * feature called templates we'll see later in the class.
 */
template <typename T>
void show_integer_info() {
    if (std::numeric_limits<T>::is_signed) {
        std::cout << " - is signed\n";
    } else {
        std::cout << " - is unsigned\n";
    }
    if (!std::is_same_v<std::decay_t<T>, decltype(+T{})>) {
        if (std::numeric_limits<T>::is_signed) {
            std::cout << " - auto-promotes to int in arithmetic\n";
        } else {
            std::cout << " - auto-promotes to int in arithmetic (i.e., becomes "
                         "*signed*)\n";
        }
    }
    int digits = std::numeric_limits<T>::digits;
    int needed_bits = std::numeric_limits<T>::is_signed ? digits + 1 : digits;
    std::cout << " - requires " << needed_bits << " bit(s)\n";
    std::cout << " - occupies " << sizeof(T) << " byte(s)\n";
    std::cout << " - range: [" << +std::numeric_limits<T>::lowest() << ".."
              << +std::numeric_limits<T>::max() << "]\n";
    std::cout << std::endl;
}

/*
 * To avoid lots of copy-and-pasted code, this function uses an advanced
 * feature we'll see later in the class.
 */
template <typename T>
void show_floating_info() {
    if (std::numeric_limits<T>::is_iec559) {
        std::cout << " - follows IEEE-754/IEC-559 standard\n";
    } else {
        std::cout << " - follows a mystery floating-point standard\n";
    }
    int radix = std::numeric_limits<T>::radix;
    std::string digits = radix == 2 ? "bits" : "digits";
    std::cout << " - radix (base) is " << radix << "\n";
    std::cout << " - exponent range [" << radix << "^"
              << std::numeric_limits<T>::min_exponent - 1 << ".." << radix
              << "^" << std::numeric_limits<T>::max_exponent - 1 << "]\n";
    std::cout << " - " << std::numeric_limits<T>::digits << " significand "
              << digits << " (about " << std::numeric_limits<T>::digits10
              << " decimal digits)\n";
    std::cout << " - occupies " << sizeof(T) << " byte(s)\n";
    int currentPrecision = std::cout.precision();
    std::cout.precision(std::numeric_limits<T>::digits10);
    std::cout << " - range: [" << std::numeric_limits<T>::lowest() << ".."
              << std::numeric_limits<T>::max() << "]\n";
    std::cout << " - smallest (accurate) value "
              << std::numeric_limits<T>::min() << "\n";
    std::cout << " - smallest (possible) value "
              << std::numeric_limits<T>::denorm_min() << "\n";
    std::cout.precision(currentPrecision);
    std::cout << std::endl;
}

template <typename T>
void show_numtype_info(std::string name) {
    std::cout << "Information about " << name << ":\n";
    std::string_view true_name = type_name<T>();
    if (true_name != name) {
        std::cout << " - is just a type alias for " << true_name
                  << " (on *this* system)\n";
    }

    // If it's an integer type, show the integer info.
    if constexpr (std::is_integral_v<T>) {
        show_integer_info<T>();
    } else if constexpr (std::is_floating_point_v<T>) {
        show_floating_info<T>();
    } else {
        std::cout << " - is neither integer nor floating-point\n";
    }
}

#define SHOW_NUMTYPE_INFO(T) show_numtype_info<T>(#T)

#endif  // SHOW_TYPES_INTERNALS_HPP_INCLUDED
