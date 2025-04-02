#include "generator.h"

#include <iostream>

generator<int> range(size_t n) {
    for (size_t i = 0; i < n; ++i) {
        co_yield i;
    }
}

int main() {
    for (auto i : range(10)) {
        std::cout << i << " ";
    }
}

