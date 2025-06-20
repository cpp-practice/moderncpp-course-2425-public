#include <cstddef> // for size_t

template <size_t N>
struct fib {
    static constexpr size_t value = fib<N-1>::value + fib<N-2>::value;
};

template <>
struct fib<0> {
    static constexpr size_t value = 0;
};

template <>
struct fib<1> {
    static constexpr size_t value = 1;
};

template <size_t N>
constexpr size_t fib_v = fib<N>::value;

int main() {
    // https://en.wikipedia.org/wiki/Fibonacci_number
    static_assert(fib_v<0> == 0);
    static_assert(fib_v<1> == 1);
    static_assert(fib_v<2> == 1);
    static_assert(fib_v<3> == 2);
    
    static_assert(fib_v<19> == 4181);
}
